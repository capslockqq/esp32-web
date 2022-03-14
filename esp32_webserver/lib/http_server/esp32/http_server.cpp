#include "http_server.hpp"

static const char *TAG = "webserver";
std::map<std::string, httpd_uri_t> HttpServer::end_points;

HttpServer::HttpServer()
{
}

esp_err_t lol(httpd_req_t *req) {
    httpd_resp_set_hdr(req, "Content-Type", "text/html");
    httpd_resp_set_hdr(req, "access-control-allow-origin", "*");
    httpd_resp_set_hdr(req, "Cache-Control", "no-cache");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    httpd_resp_send(req, "Welcome to the REST Web Server", HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

void HttpServer::register_get_endpoints(EndPointType &_end_points)
{
    for (const auto &[key, value] : _end_points)
    {
        response_container_t *rest_context = (response_container_t *)calloc(1, sizeof(response_container_t));
        *rest_context = value;
        ESP_LOGI(TAG, "%s", rest_context->endpoint.c_str());
        bool is_get_request = value.type == HttpType::GET;
        httpd_uri_t all_parameters_get = {
            .uri = rest_context->endpoint.c_str(),
            .method = (is_get_request) ? HTTP_GET : HTTP_POST,
            .handler = (is_get_request) ? parameter_get_handler : parameter_post_handler,
            .user_ctx = rest_context};
        end_points[key] = all_parameters_get;
    }
    httpd_uri_t base = {
        .uri = "/",
        .method = HTTP_GET,
        .handler = lol,
        .user_ctx = NULL};
    end_points["/"] = base;
}

void HttpServer::register_post_endpoints(std::string endpoints)
{
    httpd_uri_t uri_post = {
        .uri = endpoints.c_str(),
        .method = HTTP_POST,
        .handler = parameter_post_handler,
        .user_ctx = NULL};
}

esp_err_t HttpServer::parameter_get_handler(httpd_req_t *req)
{
    httpd_resp_set_hdr(req, "Content-Type", "application/json");
    httpd_resp_set_hdr(req, "access-control-allow-origin", "*");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    response_container_t *rest_context = (response_container_t *)req->user_ctx;
    std::string json_response = get_json_response_as_string(*rest_context);
    httpd_resp_send(req, json_response.c_str(), HTTPD_RESP_USE_STRLEN);

    /* After sending the HTTP response the old HTTP request
     * headers are lost. Check if HTTP request headers can be read now. */
    if (httpd_req_get_hdr_value_len(req, "Host") == 0)
    {
    }
    return ESP_OK;
}

esp_err_t HttpServer::parameter_post_handler(httpd_req_t *req)
{
    httpd_resp_set_hdr(req, "access-control-allow-origin", "*");
    httpd_resp_set_hdr(req, "Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
    httpd_resp_set_hdr(req, "Content-Type", "application/json");
    /* Destination buffer for content of HTTP POST request.
     * httpd_req_recv() accepts char* only, but content could
     * as well be any binary data (needs type casting).
     * In case of string data, null termination will be absent, and
     * content length would give length of string */
    char content[500];

    /* Truncate if content length larger than the buffer */
    size_t recv_size = MIN(req->content_len, sizeof(content));
    int ret = httpd_req_recv(req, content, recv_size);
    if (ret <= 0)
    { /* 0 return value indicates connection closed */
        /* Check if timeout occurred */
        if (ret == HTTPD_SOCK_ERR_TIMEOUT)
        {
            /* In case of timeout one can choose to retry calling
             * httpd_req_recv(), but to keep it simple, here we
             * respond with an HTTP 408 (Request Timeout) error */
            httpd_resp_send_408(req);
        }
        /* In case of error, returning ESP_FAIL will
         * ensure that the underlying socket is closed */
        return ESP_FAIL;
    }
    std::string raw_data = content;
    std::string json_response = raw_data.substr(0, raw_data.find_last_of("}") + 1);
    nlohmann::json received_data = nlohmann::json::parse(json_response);

    for (int i = 0; i < received_data["parameters"].size(); i++)
    {
        _parameter_bank->set_parameter_if_found(received_data["parameters"][i]);
    }

    nlohmann::json response_msg;
    response_msg["status"] = "OK";

    httpd_resp_send(req, response_msg.dump().c_str(), HTTPD_RESP_USE_STRLEN);
    return ESP_OK;
}

httpd_handle_t HttpServer::start()
{
    httpd_handle_t server = NULL;
    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.lru_purge_enable = true;

    // Start the httpd server
    if (httpd_start(&server, &config) == ESP_OK)
    {
        for (const auto &[key, value] : end_points)
        {
            httpd_register_uri_handler(server, &value);
        }
#if CONFIG_EXAMPLE_BASIC_AUTH
        httpd_register_basic_auth(server);
#endif
        return server;
    }

    return NULL;
}

void HttpServer::connect_handler(void *arg, esp_event_base_t event_base,
                                 int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server == NULL)
    {
        *server = start();
    }
}

void HttpServer::disconnect_handler(void *arg, esp_event_base_t event_base,
                                    int32_t event_id, void *event_data)
{
    httpd_handle_t *server = (httpd_handle_t *)arg;
    if (*server)
    {
        stop_webserver(*server);
        *server = NULL;
    }
}

void HttpServer::stop_webserver(httpd_handle_t server)
{
    httpd_stop(server);
}

void HttpServer::start_webserver()
{
    static httpd_handle_t server = NULL;

#ifdef CONFIG_EXAMPLE_CONNECT_WIFI
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, (esp_event_handler_t)&connect_handler, &server);
    esp_event_handler_register(WIFI_EVENT, WIFI_EVENT_STA_DISCONNECTED, (esp_event_handler_t)&disconnect_handler, &server);
#endif // CONFIG_EXAMPLE_CONNECT_WIFI
#ifdef CONFIG_EXAMPLE_CONNECT_ETHERNET
    ESP_ERROR_CHECK(esp_event_handler_register(IP_EVENT, IP_EVENT_ETH_GOT_IP, &connect_handler, &server));
    ESP_ERROR_CHECK(esp_event_handler_register(ETH_EVENT, ETHERNET_EVENT_DISCONNECTED, &disconnect_handler, &server));
#endif // CONFIG_EXAMPLE_CONNECT_ETHERNET

    /* Start the server for the first time */
    server = start();
}
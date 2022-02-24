#pragma once
#include "../http_server_interface.hpp"
#include <esp_wifi.h>
#include <esp_event.h>
#include <esp_log.h>
#include <esp_system.h>
#include <nvs_flash.h>
#include <sys/param.h>
#include "nvs_flash.h"
#include "esp_netif.h"
#include "esp_eth.h"
#include "protocol_examples_common.h"
#include "esp_tls_crypto.h"
#include <esp_http_server.h>
#include <map>

class HttpServer : public HttpServerInterface<HttpServer> {
    public:
    HttpServer();
    void start_webserver();

    private:
    static httpd_handle_t start(void);
    static esp_err_t hello_get_handler(httpd_req_t *req);
    static void connect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
    static void disconnect_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data);
    static void stop_webserver(httpd_handle_t server);
    static std::map<std::string, httpd_uri_t> end_points;
};
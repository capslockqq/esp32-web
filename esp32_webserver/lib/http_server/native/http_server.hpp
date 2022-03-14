#pragma once
#include "../http_server_interface.hpp"
#include <vector>

class HttpServer : public HttpServerInterface {
    public:
    HttpServer();
    void start_webserver();
    void register_get_endpoints(EndPointType &);
    void register_post_endpoints(std::string endpoints);

    private:
    static inline EndPointType _endpoints{};
    static void update_webserver(void* unused);
};
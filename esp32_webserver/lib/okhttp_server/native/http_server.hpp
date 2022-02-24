#pragma once
#include "../http_server_interface.hpp"

class HttpServer : public HttpServerInterface<HttpServer> {
    public:
    HttpServer();
    void start_webserver();
};
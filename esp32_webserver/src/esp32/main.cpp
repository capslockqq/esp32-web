#include "../program.hpp"
#include <esp32/http_server.hpp>
#include <http_server_interface.hpp>

extern "C" {
    void app_main(void);
}

void app_main(void) {
    HttpServerInterface<HttpServer> http_server_implementation;

    start_app(http_server_implementation);
}
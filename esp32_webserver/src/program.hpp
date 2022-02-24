#pragma once
#include <http_server_interface.hpp>


template<typename http_server>
void start_app(HttpServerInterface<http_server> http_server_implementation) {
    http_server_implementation.start_webserver();
}
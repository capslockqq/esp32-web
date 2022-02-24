#include <program.hpp>
#include <http_server_interface.hpp>
#include <native/http_server.hpp>
#include <iostream>

#define PORT 8080
int main()
{
    HttpServerInterface<HttpServer> http_server;
    start_app(http_server);
    return 0;

}
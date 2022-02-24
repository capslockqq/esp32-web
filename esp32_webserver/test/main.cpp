#include <unity.h>
#include <native/http_server.hpp>


void start_web_server() {
    HttpServer http_server;
    http_server.start_webserver();
}

int main(int argc, char const *argv[])
{
    UNITY_BEGIN();
    RUN_TEST(start_web_server);
    UNITY_END();
    return 0;
}
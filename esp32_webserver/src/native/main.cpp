#include "program.hpp"
#include <http_server_interface.hpp>
#include <native/http_server.hpp>
#include <parameter.hpp>
#include <include/FreeRTOS.h>
#include <include/task.h>
#include <time_system.hpp>
// #include <>


#define PORT 8080
// int main()
// {
//     // HttpServerInterface *http_server = new HttpServer();
//     // std::time_t result = std::time(nullptr);
//     // TimeSystem::set_initial_unixtime(result);
//     // start_app(http_server);
//     return 0;
// }

// void start_threads() {
//     vTaskStartScheduler();
// }
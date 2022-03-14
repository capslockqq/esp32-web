#include "program.hpp"
#include <http_server_interface.hpp>
#include <native/http_server.hpp>
#include <parameter.hpp>
#include <include/FreeRTOS.h>
#include <include/task.h>
#include <time_system.hpp>
#include <web/echo_handler.hpp>

void static hej()
{
    HttpServerInterface *http_server = new HttpServer();
    std::time_t result = std::time(nullptr);
    TimeSystem::set_initial_unixtime(result);
    start_app(http_server);
}

int main()
{

    broadcast_server server;

    std::thread senderThread([&server]()
                             { server.sendTest(); });

    std::thread hej2(hej);

    server.run(9002);
    hej2.join();
    senderThread.join();
    return 0;
}

void start_threads()
{
    vTaskStartScheduler();
}
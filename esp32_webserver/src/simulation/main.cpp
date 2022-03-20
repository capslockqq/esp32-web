#include "program.hpp"
#include <http_server_interface.hpp>
#include <native/http_server.hpp>
#include <parameter.hpp>
#include <include/FreeRTOS.h>
#include <include/task.h>
#include <time_system.hpp>
#include <web/echo_handler.hpp>
#include "simulation.hpp"
#include <application_interface.hpp>
#include <application/application.hpp>
#include <io_bank.hpp>
#include <application_binding.hpp>

HttpServerInterface *http_server = new HttpServer();
ProgramContainer program(http_server);
HttpServerInterface *Implementaion = new HttpServer();
ApplicationInterface *SimulationApplication = new Simulation();
ApplicationInterface *application_interface = new Application("Name", Implementaion, SimulationApplication);
auto simulation = static_cast<Simulation *>(SimulationApplication);


void stop_websocket(int sig) {
    std::cout << "STOPPING WEBSOCKET!!" << std::endl;
    simulation->stop();
    exit(1);
}


void static run_app()
{
    std::time_t result = std::time(nullptr);
    TimeSystem::set_initial_unixtime(result);
    program.start_appplications();
}

int main()
{
    struct sigaction sigIntHandler;

    sigIntHandler.sa_handler = stop_websocket;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;

    sigaction(SIGINT, &sigIntHandler, NULL);

    auto application = static_cast<Application*>(application_interface);

    program.add_application(application_interface);
    std::thread app_thread(run_app);
    simulation->setup();
    simulation->start_websocket();
    app_thread.join();
    return 0;
}

void start_threads()
{
    vTaskStartScheduler();
}
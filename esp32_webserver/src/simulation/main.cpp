#include "program.hpp"
#include <http_server_interface.hpp>
#include <native/http_server.hpp>
#include <parameter.hpp>
#include <include/FreeRTOS.h>
#include <include/task.h>
#include <time_system.hpp>
#include <web/echo_handler.hpp>
#include "simulation.hpp"
#include <application/application.hpp>
#include <io_bank.hpp>
#include <application/application_binding.hpp>

HttpServerInterface *http_server = new HttpServer();
ProgramContainer program(http_server);


void static run_app()
{
    std::time_t result = std::time(nullptr);
    TimeSystem::set_initial_unixtime(result);
    program.start_appplications();
}

int main()
{
    HttpServerInterface *Implementaion = new HttpServer();
    ApplicationInterface *SimulationApplication = new Simulation();
    ApplicationInterface *application = new Application("Name", Implementaion, SimulationApplication);
    bind_system(static_cast<Application *>(application));
    program.add_application(application);
    std::thread app_thread(run_app);
    auto simulation = static_cast<Simulation *>(SimulationApplication);
    simulation->setup();
    simulation->start_websocket();
    app_thread.join();
    return 0;
}

void start_threads()
{
    vTaskStartScheduler();
}
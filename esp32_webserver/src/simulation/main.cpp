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

HttpServerInterface *http_server = new HttpServer();
ProgramContainer program(http_server);


void static run_app()
{
    std::time_t result = std::time(nullptr);
    TimeSystem::set_initial_unixtime(result);
    program.start_appplications();
}

void some_thread(broadcast_server* server) {
    auto applications = program.get_applications();
    auto application = applications.at(0);
    std::mutex *m = application->get_mutex();
    std::condition_variable *cv = application->get_conditional();
    while(1) {
        std::unique_lock<std::mutex> lk(*m);
        cv->wait(lk);
        server->sendTest();
        cv->notify_one();
    }
}

int main()
{   
    std::condition_variable cv;
    std::mutex m;
    HttpServerInterface *implementaion = new HttpServer();
    ApplicationInterface *application = new Application("Name", implementaion, &cv, &m);
    ApplicationInterface* SimulationApplication = new Simulation(&cv, &m);
    program.add_application(application);
    program.add_application(SimulationApplication);
    std::thread app_thread(run_app);
    auto simulation = static_cast<Simulation*>(SimulationApplication);
    simulation->start_websocket();
    app_thread.join();
    return 0;
}

void start_threads()
{
    vTaskStartScheduler();
}
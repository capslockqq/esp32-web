#include "program.hpp"
#include <setup_webserver.hpp>
#include <parameter_bank.hpp>
#include <time_system.hpp>
#include <thread>
#include <application.hpp>
#include <tasks/application_tasks.hpp>

void wait_for_unixtime()
{
    while (!TimeSystem::get_current_unixtime())
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
}

ProgramContainer::ProgramContainer(HttpServerInterface *implemetation)
{
    // ApplicationInterface *application = new Application("Name", implemetation);
    // _applications.push_back(application);
}

void ProgramContainer::add_application(ApplicationInterface *application)
{
    _applications.push_back(application);
}

void ProgramContainer::start_appplications()
{
    wait_for_unixtime();
    Tasks tasks(_applications);
    start_threads();
}

std::vector<ApplicationInterface*> ProgramContainer::get_applications() {
    return _applications;
}
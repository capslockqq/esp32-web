#include "application_tasks.hpp"

Tasks::Tasks(std::vector<ApplicationInterface *> applications) : _applications(applications)
{
    for (auto application : _applications)
    {
        application->start_task();
    }
}

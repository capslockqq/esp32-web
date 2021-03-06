#include "notify.hpp"

void Notify::notify_all()
{
    if (!_application)
        return;
    _application->Update();
}

Notify::Notify(ApplicationInterface *application) : _application(application)
{
}

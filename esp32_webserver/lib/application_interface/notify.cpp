#include "notify.hpp"
#include <iostream>

void Notify::notify_all()
{
    if (!_application)
        return;
    _application->Update();
}

Notify::Notify(ApplicationInterface *application) : _application(application)
{
}

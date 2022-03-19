#pragma once
#include "application_interface.hpp"

class Notify
{
public:
    Notify() {}
    Notify(ApplicationInterface *application);
    void notify_all();

private:
    ApplicationInterface *_application;
};

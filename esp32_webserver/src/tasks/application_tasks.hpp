#pragma once
#include <vector>
#include <application/application_interface.hpp>
class Tasks
{
public:
    Tasks(std::vector<ApplicationInterface *> applications);

private:
    std::vector<ApplicationInterface *> _applications;
};
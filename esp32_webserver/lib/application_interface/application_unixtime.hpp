#pragma once
#include <application_interface.hpp>
#include <string>

class ApplicationUnixtime : public ApplicationInterface { 
    public:
    ApplicationUnixtime(std::string name);
    void Update();
};
#pragma once
#include <string>
#include <http_server_interface.hpp>
#include <application_interface.hpp>
#include <project_name.hpp>
#include <notify.hpp>
#include <output.hpp>
#include <input.hpp>

class Application : public ApplicationInterface, public Notify
{
public:
    Application(std::string name, HttpServerInterface *http_server_implementation);
    Application(std::string name, HttpServerInterface *http_server_implementation, ApplicationInterface *application);
    void Update();

private:
    HttpServerInterface *_http_server_implementation;
    Parameter<int> _sample_frequency;
    ProjectName _project_name;
    
};
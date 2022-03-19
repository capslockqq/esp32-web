#pragma once
#include <string>
#include <http_server_interface.hpp>
#include <application/application_interface.hpp>
#include <application/notify.hpp>
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
};
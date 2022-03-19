#include "application.hpp"
#include <web/setup_webserver.hpp>
#include <iostream>

Application::Application(std::string name, HttpServerInterface *http_server_implementation, ApplicationInterface *application) : ApplicationInterface(name, FREQUENCY),
                                                                                                                                 Notify(application),
                                                                                                                                 _http_server_implementation(http_server_implementation),
                                                                                                                                 _sample_frequency("Sample frequency", "sample-freq", FREQUENCY,  "hz")
{
    register_endpoints_and_start_webserver(http_server_implementation);
}

Application::Application(std::string name, HttpServerInterface *http_server_implementation) : Application(name, http_server_implementation, nullptr)
{
}

void Application::Update()
{
    this->notify_all();
}

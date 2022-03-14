#include "application.hpp"
#include <web/setup_webserver.hpp>
#include <iostream>
Application::Application(std::string name, HttpServerInterface *http_server_implementation, std::condition_variable *cv, std::mutex *m) : ApplicationInterface(name, cv, m, 100, true),
                                                                                              _http_server_implementation(http_server_implementation),
                                                                                              _output(Output<int>("Output 1", "some id", 0)),
                                                                                              _input(Input<int>("Output 1", "some id", 0)),
                                                                                              param1("Some name", "some_id", 33)
{
    register_endpoints_and_start_webserver(http_server_implementation);
    _input.set_value_source(&_output);
}

void Application::Update()
{
    std::cout << "Hello from app" << std::endl;
    _output.set_value(_output.get_value() + 1);
}

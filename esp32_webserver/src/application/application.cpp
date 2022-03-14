#include "application.hpp"
#include <web/setup_webserver.hpp>


Application::Application(std::string name, HttpServerInterface *http_server_implementation) : ApplicationInterface(name),
                                                                                              _http_server_implementation(http_server_implementation),
                                                                                              _output(Output<int>("Output 1", "some id", 0)),
                                                                                              _input(Input<int>("Output 1", "some id", 0))
{
    register_endpoints_and_start_webserver(http_server_implementation);
    _input.set_value_source(&_output);
}

void Application::Update()
{
    _output.set_value(_output.get_value() + 1);
}

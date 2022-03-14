#pragma once
#include <string>
#include <http_server_interface.hpp>
#include <application/application_interface.hpp>
#include <output.hpp>
#include <input.hpp>

class Application : public ApplicationInterface
{
public:
    Application(std::string name, HttpServerInterface *http_server_implementation, std::condition_variable *cv, std::mutex *m);
    void Update();

private:
    HttpServerInterface *_http_server_implementation;
    Output<int> _output;
    Input<int> _input;
    Parameter<int> param1;

};
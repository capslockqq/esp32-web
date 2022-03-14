#include "setup_webserver.hpp"

response_container_t generate_all_parameter_data(ParamList* parameters)
{
    response_container_t response;
    response.endpoint = "/AllParameters";
    response.type = HttpType::GET;
    auto lambdaPrintVisitor = [&response](auto parameter)
    {
        response.data[parameter.get_id()] = parameter;
    };
    for (auto &[key, value] : *parameters)
    {
        std::visit(lambdaPrintVisitor, value);
    }
    return response;
}

void register_endpoints_and_start_webserver(HttpServerInterface *http_server_implementation)
{
    auto parameter_bank = ParameterBank::get_instance();
    auto all_parameters_response = generate_all_parameter_data(parameter_bank->get_parameters());
    EndPointType get_endpoints = {
        {all_parameters_response.endpoint, all_parameters_response},
        {"/SetParameters", response_container_t{
                               .endpoint = "/SetParameters",
                               .type = HttpType::POST,
                           }}};
    http_server_implementation->register_get_endpoints(get_endpoints);
    http_server_implementation->register_post_endpoints("/SetParameters");
    http_server_implementation->start_webserver();
}
#include <parameter_bank.hpp>
#include <http_server_interface.hpp>

void register_endpoints_and_start_webserver(HttpServerInterface *http_server_implementation);
response_container_t generate_all_parameter_data(ParamList parameters);
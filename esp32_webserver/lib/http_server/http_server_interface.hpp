#pragma once
#include <map>
#include <any>
#include <json.hpp>
#include <value_system.hpp>
#include <parameter.hpp>
#include <variant>

using ResponseData = std::map<std::string, std::variant<Parameter<int>, Parameter<float>, Parameter<double>, Parameter<std::string>>>;

enum class HttpType
{
    GET,
    POST
};

typedef struct json_response
{
    ResponseData data;
    std::string endpoint;
    nlohmann::json j;
    HttpType type;

} response_container_t;

using EndPointType = std::map<std::string, response_container_t>;

class HttpServerInterface
{
public:
    virtual void start_webserver() = 0;
    virtual void register_get_endpoints(EndPointType &endpoints) = 0;
    virtual void register_post_endpoints(std::string endpoints) = 0;

    static std::string get_json_response_as_string(response_container_t &response_container)
    {
        nlohmann::json json_response;
        auto lambdaPrintVisitor = [&json_response](auto _in)
        {
            json_response["parameters"].push_back({{"id", _in.get_id()},
                                                   {"name", _in.get_name()},
                                                   {"value", _in.get_value()},
                                                   {"unit", _in.get_unit()},
                                                   {"last_updated_unixtime_ms", static_cast<long long int>(_in.get_unixtime_ms())}});
        };
        for (const auto &[key, value] : response_container.data)
        {
            std::visit(lambdaPrintVisitor, value);
        }
        return json_response.dump();
    }
};
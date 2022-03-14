#pragma once
#include <map>
#include <any>
#include <variant>
#include <parameter.hpp>
#include <json.hpp>

class ParameterBank
{
public:
    static ParameterBank *get_instance();
    ParamList* get_parameters();
    void set_parameter_if_found(nlohmann::json param);
    template <class T>
    void store_parameter(Parameter<T> *param)
    {
        {
            _parameters[param->get_id()] = *param;
        }
    }

private:
    inline static ParameterBank* _ptr = nullptr;
    ParameterBank();
    ParamList _parameters;
    inline static nlohmann::json latest_value {};
};

#include <parameter_bank.hpp>

ParameterBank *ParameterBank::get_instance()
{
    if (_ptr == NULL)
        _ptr = new ParameterBank();
    return _ptr;
}

ParameterBank::ParameterBank() : _parameters{}
{
}


ParamList *ParameterBank::get_parameters()
{
    return &_parameters;
}


void ParameterBank::set_parameter_if_found(nlohmann::json param)
{
    struct VisitPackage
    {
        void operator()(Parameter<int> &param) { param.set_value(latest_value); }
        void operator()(Parameter<float> &param) { param.set_value(latest_value); }
        void operator()(Parameter<double> &param) { param.set_value(latest_value); }
        void operator()(Parameter<std::string> &param) { param.set_value(latest_value); }
    };
    auto id = param["id"].get<std::string>();
    if (_parameters.find(id) != _parameters.end())
    {
        latest_value = param["new_value"];
        std::visit(VisitPackage(), _parameters[id]);
    }
}

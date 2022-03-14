#pragma once
#include <string>
#include <value_system.hpp>
#include <variant>
#include <map>

template <typename T>
class Parameter : public ValueSystem<T>
{
public:
    Parameter() : ValueSystem<T>()
    {
    }
    Parameter(std::string name, std::string id, T value, std::string unit = "");
};

using ParameterTypes = std::variant<Parameter<int>, Parameter<float>, Parameter<double>, Parameter<std::string>>;
using ParamList = std::map<std::string, ParameterTypes>;

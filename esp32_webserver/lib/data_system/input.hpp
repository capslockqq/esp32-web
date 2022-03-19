#pragma once
#include <parameter.hpp>
#include <value_system.hpp>
#include <output.hpp>

template <typename T>
class Input : public ValueSystem<T>
{
public:
    Input() : ValueSystem<T>() {}
    Input(std::string name, std::string id, T value, std::string unit = "");
};

using InputTypes = std::variant<Input<int>*, Input<float>*, Input<double>*, Input<std::string>*>;
using InputList = std::map<std::string, InputTypes>;
#pragma once
#include <variant>
#include <map>
#include <value_system.hpp>

template <typename T>
class Output : public ValueSystem<T>
{
public:
    Output() : ValueSystem<T>() {}
    Output(std::string name, std::string id, T value, std::string unit = "");
};

using OutputTypes = std::variant<Output<int>*, Output<float>*, Output<double>*, Output<std::string>*>;
using OutputList = std::map<std::string, OutputTypes>;
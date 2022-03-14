#pragma once
#include <parameter.hpp>
#include <value_system.hpp>

template <typename T>
class Output : public ValueSystem<T>
{
public:
    Output() : ValueSystem<T>() {}
    Output(std::string name, std::string id, T value, std::string unit = "") : ValueSystem<T>(name, id, value, unit)
    {
    }
};
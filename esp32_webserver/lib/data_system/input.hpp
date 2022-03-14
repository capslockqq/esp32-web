#pragma once
#include <parameter.hpp>
#include <value_system.hpp>
#include <output.hpp>

template <typename T>
class Input : public ValueSystem<T>
{
public:
    Input() : ValueSystem<T>() {}
    Input(std::string name, std::string id, T value, std::string unit = "") : ValueSystem<T>(name, id, value, unit)
    {
    }
};
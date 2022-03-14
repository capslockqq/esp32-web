#include <parameter.hpp>
#include <parameter_bank.hpp>


template <typename T>
Parameter<T>::Parameter(std::string name, std::string id, T value, std::string unit) : ValueSystem<T>(name, id, value, unit)
{
    ParameterBank* parameter_bank = ParameterBank::get_instance();
    parameter_bank->store_parameter<T>(this);
}

template class Parameter<int>;
template class Parameter<float>;
template class Parameter<double>;
template class Parameter<std::string>;
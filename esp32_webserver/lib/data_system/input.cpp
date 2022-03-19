#include "input.hpp"
#include "io_bank.hpp"

template <typename T>
Input<T>::Input(std::string name, std::string id, T value, std::string unit) : ValueSystem<T>(name, id, value, unit)
{
    IOBank *io_bank = IOBank::get_instance();
    io_bank->store_input<T>(this);
}

template class Input<int>;
template class Input<float>;
template class Input<double>;
template class Input<std::string>;
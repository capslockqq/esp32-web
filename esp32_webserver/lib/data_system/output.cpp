#include "output.hpp"
#include "io_bank.hpp"

template <typename T>
Output<T>::Output(std::string name, std::string id, T value, std::string unit) : ValueSystem<T>(name, id, value, unit)
{
    IOBank *io_bank = IOBank::get_instance();
    io_bank->store_output<T>(this);
}

template class Output<int>;
template class Output<float>;
template class Output<double>;
template class Output<std::string>;
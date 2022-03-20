#include <output.hpp>
#include <input.hpp>


template<typename T>
void io_bind(Output<T> *output, Input<T> *input) {
    input->set_value_source(output);
}
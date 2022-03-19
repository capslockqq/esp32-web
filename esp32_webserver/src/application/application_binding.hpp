#include <output.hpp>
#include <input.hpp>
#include "application.hpp"

void bind_system(Application *application);

template<typename T>
void io_bind(Output<T> *output, Input<T> *input) {
    input->set_value_source(output);
}
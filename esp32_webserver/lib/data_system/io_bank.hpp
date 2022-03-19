#pragma once
#include <map>
#include <any>
#include <variant>
#include <output.hpp>
#include <input.hpp>
#include <json.hpp>

class IOBank
{
public:
    static IOBank *get_instance();
    OutputList *get_outputs();
    InputList *get_inputs();
    void set_output_if_found(nlohmann::json param);
    void set_input_if_found(nlohmann::json param);
    template <class T>
    void store_output(Output<T> *output)
    {
        _outputs[output->get_id()] = output;
    }
    template <class T>
    void store_input(Input<T> *input) {
        _inputs[input->get_id()] = input;
    }

private:
    inline static IOBank *_ptr = nullptr;
    IOBank();
    OutputList _outputs;
    InputList _inputs;
    inline static nlohmann::json latest_value{};
};

#include "io_bank.hpp"

IOBank *IOBank::get_instance()
{
    if (_ptr == NULL)
        _ptr = new IOBank();
    return _ptr;
}

IOBank::IOBank() : _outputs{}
{
}

OutputList *IOBank::get_outputs()
{
    return &_outputs;
}

InputList *IOBank::get_inputs()
{
    return &_inputs;
}

void IOBank::set_output_if_found(nlohmann::json output)
{
    struct VisitPackage
    {
        void operator()(Output<int> *output) { output->set_value(latest_value); }
        void operator()(Output<float> *output) { output->set_value(latest_value); }
        void operator()(Output<double> *output) { output->set_value(latest_value); }
        void operator()(Output<std::string> *output) { output->set_value(latest_value); }
    };
    auto id = output["id"].get<std::string>();
    if (_outputs.find(id) != _outputs.end())
    {
        latest_value = output["value"];
        std::visit(VisitPackage(), _outputs[id]);
    }
}

void IOBank::set_input_if_found(nlohmann::json input)
{
    struct VisitPackage
    {
        void operator()(Input<int> *input)
        {
            input->remove_value_source();
            input->set_value(latest_value);
        }
        void operator()(Input<float> *input)
        {
            input->remove_value_source();
            input->set_value(latest_value);
        }
        void operator()(Input<double> *input)
        {
            input->remove_value_source();
            input->set_value(latest_value);
        }
        void operator()(Input<std::string> *input)
        {
            input->remove_value_source();
            input->set_value(latest_value);
        }
    };
    auto id = input["id"].get<std::string>();
    if (_inputs.find(id) != _inputs.end())
    {
        latest_value = input["value"];
        std::visit(VisitPackage(), _inputs[id]);
    }
}

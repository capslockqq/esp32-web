#include "simulation.hpp"
#include <iostream>
#include <io_bank.hpp>
#include <ctime>
#include <cstdlib>

Simulation::Simulation() : ApplicationInterface("Simulation system", 0),
                           simulation_length("Simulation length", "simulation-length", 30, "seconds"),
                           simulation_ticks("Simulation ticks", "simu-ticks", 0, "samples")
{
    _server = new broadcast_server();
}

void Simulation::stop() {
    _server->stop();
}

void Simulation::setup()
{
    auto instance = IOBank::get_instance();
    auto outputs = instance->get_outputs();
    auto inputs = instance->get_inputs();
    auto output_visitor = [this](auto output)
    {
        output_data[output->get_id()] = output;
    };
    for (auto &[key, value] : *outputs)
    {
        std::visit(output_visitor, value);
    }
    auto input_visitor = [this](auto input)
    {
        input_data[input->get_id()] = input;
    };
    for (auto &[key, value] : *inputs)
    {
        std::visit(input_visitor, value);
    }
    json_payload_all_inputs_and_outputs = generate_payload();
    json_payload_all_inputs_and_outputs["all_data"] = true;
    _server->set_all_inputs_and_outputs_payload(json_payload_all_inputs_and_outputs);
}

void Simulation::Update()
{
    static int ticks = 1;
    json_payload = generate_payload();
    _server->set_payload(json_payload);
    json_payload["all_data"] = true;
    _server->set_all_inputs_and_outputs_payload(json_payload);
    _server->send_payload();
    while (!_server->done_simulating)
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    }
    nlohmann::json received_payload = _server->get_reveived_payload();
    auto instance = IOBank::get_instance();
    if (!received_payload["inputs"].empty())
    {
        for (int i = 0; i < received_payload["inputs"].size(); i++)
        {
            instance->set_input_if_found(received_payload["inputs"][i]);
        }
    }

    _server->done_simulating = false;
    simulation_ticks.set_value(rand() % 10);
}

void Simulation::start_websocket()
{
    _server->run(9011);
}

nlohmann::json Simulation::generate_payload()
{
    nlohmann::json payload;

    auto formatPayload = [&payload](std::string index, auto _in)
    {
        payload[index].push_back({{"id", _in->get_id()},
                                  {"name", _in->get_name()},
                                  {"value", _in->get_value()},
                                  {"unit", _in->get_unit()},
                                  {"last_updated_unixtime_ms", static_cast<long long int>(_in->get_unixtime_ms())}});
    };

    auto output_visitor = [this, &formatPayload](auto _in)
    {
        formatPayload("outputs", _in);
    };
    for (const auto &[key, value] : output_data)
    {
        std::visit(output_visitor, value);
    }
    auto input_visitor = [this, &formatPayload](auto _in)
    {
        formatPayload("inputs", _in);
    };
    for (const auto &[key, value] : input_data)
    {
        std::visit(input_visitor, value);
    }
    return payload;
}

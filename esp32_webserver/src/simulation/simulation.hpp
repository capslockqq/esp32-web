#pragma once

#include <condition_variable>
#include <mutex>
#include <echo_handler.hpp>
#include <application_interface.hpp>
#include <output.hpp>
#include <input.hpp>
#include <json.hpp>
#include <iostream>

using OutputData = std::map<std::string, std::variant<Output<int>*, Output<float>*, Output<double>*, Output<std::string>*>>;
using InputData = std::map<std::string, std::variant<Input<int>*, Input<float>*, Input<double>*, Input<std::string>*>>;

class Simulation : public ApplicationInterface
{
public:
    Simulation();
    void stop();
    void setup();
    void Update();
    void start_websocket();
    nlohmann::json generate_payload();

private:
    Parameter<int> simulation_length;
    Output<int> simulation_ticks;
    nlohmann::json json_payload;
    nlohmann::json json_payload_all_inputs_and_outputs;
    broadcast_server *_server;
    OutputData output_data;
    InputData input_data;
};
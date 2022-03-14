#pragma once

#include <condition_variable>
#include <mutex>
#include <web/echo_handler.hpp>
#include <application/application_interface.hpp>

class Simulation :public ApplicationInterface {
    public:
    Simulation(std::condition_variable *cv, std::mutex *m);
    void Update();
    void start_websocket();

    private:
    broadcast_server *_server;
};
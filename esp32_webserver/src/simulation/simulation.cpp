#include "simulation.hpp"

Simulation::Simulation(std::condition_variable *cv, std::mutex *m) : ApplicationInterface("Simulation system", cv, m, 0, true)
{
    _server = new broadcast_server();
}

void Simulation::Update()
{
    // std::unique_lock<std::mutex> lk(*this->_m);
    // this->_cv->notify_one();
    _server->sendTest();
    // this->_cv->wait(lk);
}

void Simulation::start_websocket()
{
    _server->run(9002);
}

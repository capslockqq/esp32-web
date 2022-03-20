#pragma once
#include <iostream>
#include <set>
#include <thread>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <json.hpp>
#include <boost/asio.hpp>



typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::bind;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

class broadcast_server
{
public:
    bool done_simulating;
    typedef std::set<connection_hdl, std::owner_less<connection_hdl>> con_list;
    server m_server;
    con_list m_connections;
    broadcast_server() : done_simulating(false)
    {
        m_server.init_asio();
        m_server.clear_access_channels(websocketpp::log::alevel::all);
        m_server.set_open_handler(bind(&broadcast_server::on_open, this, ::_1));
        m_server.set_close_handler(bind(&broadcast_server::on_close, this, ::_1));
        m_server.set_message_handler(bind(&broadcast_server::on_message, this, ::_1, ::_2));
    }

    void stop() {
        m_server.stop_listening();
        for (auto &connection: m_connections) {
            m_server.close(connection, websocketpp::close::status::normal, "Server stopping");
        }
    }

    void on_open(connection_hdl hdl)
    {
        m_connections.insert(hdl);
        send_all_inputs_and_outputs();
    }

    void on_close(connection_hdl hdl)
    {
        m_connections.erase(hdl);
    }

    void run(uint16_t port)
    {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }

    void on_message(connection_hdl hdl, server::message_ptr msg)
    {
        _received_payload = nlohmann::json::parse(msg->get_payload());
        done_simulating = true;
    }

    void send_payload()
    {
        static nlohmann::json old_payload;
        if (old_payload.empty())
        {
            old_payload = _payload;
            return;
        }
        std::cout << "Payload:" << old_payload.dump() << std::endl;
        std::string diff = nlohmann::json::diff(old_payload, _payload).dump();
        std::cout << "Diff:" << diff << std::endl;

        old_payload = _payload;
        for (auto connection : m_connections)
        {
            m_server.send(connection, diff, websocketpp::frame::opcode::text);
        }
    }

    void send_all_inputs_and_outputs()
    {
        for (auto connection : m_connections)
        {
            m_server.send(connection, _all_inputs_and_outputs.dump(), websocketpp::frame::opcode::text);
        }
    }

    void set_payload(nlohmann::json payload)
    {
        _payload = payload;
    }
    void set_all_inputs_and_outputs_payload(nlohmann::json payload)
    {
        _all_inputs_and_outputs = payload;
    }

    nlohmann::json get_reveived_payload() {
        return _received_payload;
    }

private:
    nlohmann::json _payload;
    nlohmann::json _received_payload;
    nlohmann::json _all_inputs_and_outputs;
};
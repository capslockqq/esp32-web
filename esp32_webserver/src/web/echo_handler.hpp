#pragma once
#include <iostream>
#include <set>
#include <thread>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> server;

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;


class broadcast_server
{

public:
    typedef std::set<connection_hdl, std::owner_less<connection_hdl>> con_list;
    server m_server;
    con_list m_connections;

    broadcast_server() {
        m_server.init_asio();

        m_server.set_open_handler(bind(&broadcast_server::on_open, this, ::_1));
        m_server.set_close_handler(bind(&broadcast_server::on_close, this, ::_1));
    }

    void on_open(connection_hdl hdl) {
        m_connections.insert(hdl);
    }

    void on_close(connection_hdl hdl) {
        m_connections.erase(hdl);
    }

    void run(uint16_t port) {
        m_server.listen(port);
        m_server.start_accept();
        m_server.run();
    }

    void sendTest()
    {
        for (auto it : m_connections) {
            m_server.send(it, "TEEEEEST", websocketpp::frame::opcode::text);
        }
    }
};
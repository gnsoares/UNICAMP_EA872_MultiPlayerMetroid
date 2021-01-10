#ifndef METROID_RECEIVERS_H
#define METROID_RECEIVERS_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "json.hpp"

using boost::asio::ip::udp;
using nlohmann::json;


namespace Receivers {

    void handshakes(
        int n,
        std::vector<std::string> *addresses,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    void otherPlayers(
        std::vector<std::string> *addresses,
        std::string my_ip_address,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    void state(
        json *state,
        std::vector<std::string> addresses,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );
}

#endif

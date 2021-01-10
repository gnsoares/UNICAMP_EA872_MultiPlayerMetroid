#ifndef METROID_TRANSMITTERS_H
#define METROID_TRANSMITTERS_H

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "json.hpp"

using boost::asio::ip::udp;
using nlohmann::json;


namespace Transmitters {

    void handshake(
        std::string hostIP,
        std::string message,
        int port,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    void otherPlayers(
        std::vector<std::string> addresses,
        int port,
        udp::socket *socket
    );

    void state(
        json state,
        std::vector<std::string> addresses,
        int port,
        std::string my_ip_address,
        udp::socket *socket
    );
}

#endif

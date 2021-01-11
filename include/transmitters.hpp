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


    /*! \brief Sends handshake to other players
     * 
     * Configuration of the handshake
     * 
     * \param host IP
     * \param message to confirm handshake
     * \param port number
     * \param socket
     * \param endpoint
     * \return nothing
     */

    void handshake(
        std::string hostIP,
        std::string message,
        int port,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    /*! \brief Estabilishes connection with other players
     * 
     * \param vector containing other players' adresses (IPs)
     * \param port number
     * \param socket
     */

    void otherPlayers(
        std::vector<std::string> addresses,
        int port,
        udp::socket *socket
    );

    /*! \brief Sends the player's game state to other players
     *
     * \param json containing player's state
     * \param port number
     * \param player's IP address
     * \param socket
     */

    void state(
        json state,
        std::vector<std::string> addresses,
        int port,
        std::string my_ip_address,
        udp::socket *socket
    );
}

#endif

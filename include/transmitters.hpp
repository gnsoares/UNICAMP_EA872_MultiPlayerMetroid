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
<<<<<<< HEAD
     * \param hostIP host IP
     * \param message message to confirm handshake
     * \param portport number
     * \param socket socket
     * \param endpoint endpoint
=======
     * \param host IP
     * \param message to confirm handshake
     * \param port number
     * \param socket
     * \param endpoint
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
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
<<<<<<< HEAD
     * \param adresses vector containing other players' adresses (IPs)
     * \param port port number
     * \param scoket socket
=======
     * \param vector containing other players' adresses (IPs)
     * \param port number
     * \param socket
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
     */

    void otherPlayers(
        std::vector<std::string> addresses,
        int port,
        udp::socket *socket
    );

    /*! \brief Sends the player's game state to other players
     *
<<<<<<< HEAD
     * \param state json containing player's state
     * \param port port number
     * \param adresses player's IP address
     * \param socket socket
=======
     * \param json containing player's state
     * \param port number
     * \param player's IP address
     * \param socket
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
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

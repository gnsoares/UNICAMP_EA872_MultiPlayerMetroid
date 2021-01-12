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

    /*! \brief Receives handshakes from other players
     *
<<<<<<< HEAD
     * \param n number of players
     * \param adresses vector containing other players' IPs
     * \param socket socket
     * \param endpoint endpoint
     * \param size integer equivalent to number of players
=======
     * \param vector containing other players' IPs
     * \param socket
     * \param endpoint
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
     * \return nothing
     */

    void handshakes(
        int n,
        std::vector<std::string> *addresses,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    /*! \brief Receives other players' connection infos
<<<<<<< HEAD
     * \param adresses vector containing other player's adresses
     * \param my_ip_address strhing containing the player ip adress
     * \param socket socket
     * \param endpoint endpoint
     * \param size integer equivalent to number of players
=======
     * \param vector containing other player's adresses
     * \param strhing containing the player ip adress
     * \param socket
     * \param endpoint
     * \param integer equivalent to number of players
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
     */

    void otherPlayers(
        std::vector<std::string> *addresses,
        std::string my_ip_address,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );

    /*! \brief Receives other players' game states
     *
<<<<<<< HEAD
     * \param state json containing other players' states
     * \param adresses other players' IP addresses
     * \param socket socket
     * \param endpoint endpoint
=======
     * \param json containing other players' states
     * \param other players' IP addresses
     * \param socket
     * \param endpoint
>>>>>>> c46a2cbb39d6efa273c6456bf550b47075028c26
     * \return nothing
     */
    void state(
        json *state,
        std::vector<std::string> addresses,
        udp::socket *socket,
        udp::endpoint endpoint,
        int size
    );
}

#endif

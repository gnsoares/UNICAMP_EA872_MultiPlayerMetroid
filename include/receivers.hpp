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
     * \param n number of players
     * \param adresses vector containing other players' IPs
     * \param socket socket
     * \param endpoint endpoint
     * \param size integer equivalent to number of players
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
     * \param adresses vector containing other player's adresses
     * \param my_ip_address strhing containing the player ip adress
     * \param socket socket
     * \param endpoint endpoint
     * \param size integer equivalent to number of players
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
     * \param state json containing other players' states
     * \param adresses other players' IP addresses
     * \param socket socket
     * \param endpoint endpoint
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

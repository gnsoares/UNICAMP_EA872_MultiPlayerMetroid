#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "json.hpp"
#include "receivers.hpp"
#include "utils.hpp"

using boost::asio::ip::udp;
using nlohmann::json;


void receiveOneHandshake(
    std::vector<std::string> *addresses,
    udp::socket *socket,
    udp::endpoint endpoint,
    int size
) {

    char buffer[size];

    (*socket).receive_from(boost::asio::buffer(buffer, size), endpoint);

    std::cout << "Pedido de handshake recebido de "
                << endpoint.address()
                << ": "
                << buffer << std::endl;

    // Respondendo a mensagem
    std::string msg("Handshake aceito!");
    (*socket).send_to(boost::asio::buffer(msg), endpoint);

    std::cout << "Mensagem de retorno enviada para "
                << endpoint.address() << std::endl;

    (*addresses).push_back(endpoint.address().to_string());

}


void Receivers::handshakes(
    int n,
    std::vector<std::string> *addresses,
    udp::socket *socket,
    udp::endpoint endpoint,
    int size
) {

    std::cout << "Esperando jogadores!" << std::endl;

    std::vector<std::thread> threads;

    for (int i = 0; i < n; i++)
        threads.push_back(std::thread(
            receiveOneHandshake, addresses, socket, endpoint, size
        ));

    for (int i = 0; i < n; threads[i++].join());
}


void Receivers::otherPlayers(
    std::vector<std::string> *addresses,
    std::string my_ip_address,
    udp::socket *socket,
    udp::endpoint endpoint,
    int size
) {

    char buffer[size];

    // receive other players list
    (*socket).receive_from(boost::asio::buffer(buffer, size), endpoint);

    auto received = json::parse(validateJsonString(std::string(buffer)));

    for (int i = 0; i < received["otherPlayers"].size(); i++)
        if (received["otherPlayers"][i] != my_ip_address)
            (*addresses).push_back(received["otherPlayers"][i]);
}


void Receivers::state(
    json *state,
    std::vector<std::string> addresses,
    udp::socket *socket,
    udp::endpoint endpoint,
    int size
) {

    std::string address;
    char buffer[size];

    while (true) {

        // receive state from other players
        (*socket).receive_from(boost::asio::buffer(buffer, size), endpoint);

        // store received state in local game state
        address = endpoint.address().to_string();

        if (std::find(addresses.begin(), addresses.end(), address) != addresses.end()) {
            auto received = json::parse(validateJsonString(std::string(buffer)));
            (*state)[address] = received;
        }
    }
}

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <string>
#include <thread>
#include <vector>

#include "json.hpp"
#include "transmitters.hpp"

using boost::asio::ip::udp;
using nlohmann::json;


void Transmitters::handshake(
    std::string hostIP,
    std::string message,
    int port,
    udp::socket *socket,
    udp::endpoint endpoint,
    int size
) {

    // Encontrando IP remoto
    boost::asio::ip::address ip_remoto =
        boost::asio::ip::address::from_string(hostIP);

    udp::endpoint remote_endpoint(ip_remoto, port);

    (*socket).send_to(
        boost::asio::buffer(message),
        remote_endpoint
    );

    std::cout << "Handshake enviado: " << message << std::endl;

    // Recebendo mensagem de retorno
    char recv[size];
    (*socket).receive_from(boost::asio::buffer(recv, size), remote_endpoint);

    std::cout << "Recebeu retorno: " << recv << std::endl;
}


void Transmitters::otherPlayers(
    std::vector<std::string> addresses,
    int port,
    udp::socket *socket
) {

    json output;
    output["otherPlayers"] = addresses;

    for (int i = 0; i < addresses.size(); i++) {

        // Encontrando IP remoto
        boost::asio::ip::address ip_remoto =
            boost::asio::ip::address::from_string(addresses[i]);

        udp::endpoint remote_endpoint(ip_remoto, port);

        (*socket).send_to(
            boost::asio::buffer(output.dump()),
            remote_endpoint
        );

    }
}


void transmitOneState(
    json const state,
    std::string address,
    int port,
    std::string my_ip_address,
    udp::socket *socket
) {

    // Encontrando IP remoto
    boost::asio::ip::address ip_remoto =
        boost::asio::ip::address::from_string(address);

    udp::endpoint remote_endpoint(ip_remoto, port);

    (*socket).send_to(
        boost::asio::buffer(state[my_ip_address].dump()),
        remote_endpoint
    );

}


void Transmitters::state(
    json state,
    std::vector<std::string> addresses,
    int port,
    std::string my_ip_address,
    udp::socket *socket
) {

    std::vector<std::thread> threads;

    if (!state.contains(my_ip_address))
        return;

    for (int i = 0; i < addresses.size(); i++)
        threads.push_back(
            std::thread(
                transmitOneState,
                state,
                addresses[i++],
                port,
                my_ip_address,
                socket
            )
        );

    for (int j = 0; j < threads.size(); threads[j++].join());
}

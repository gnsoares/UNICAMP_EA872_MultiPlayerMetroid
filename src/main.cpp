#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/program_options.hpp>
#include <chrono>
#include <iostream>
#include <iterator>
#include <SDL2/SDL.h>
#include <string>
#include <thread>
#include <vector>

#include "controllers.hpp"
#include "json.hpp"
#include "receivers.hpp"
#include "transmitters.hpp"

using boost::asio::ip::udp;
using nlohmann::json;

using namespace boost::program_options;

#define MAX_STATE_SIZE 0x2000
#define PORT 5000

std::vector<std::string> otherPlayers;
boost::asio::io_service my_io_service;
udp::endpoint local_endpoint(udp::v4(), PORT);
udp::socket my_socket(my_io_service, local_endpoint);
udp::endpoint remote_endpoint;
json state = json::object({});


void transmitState(std::string my_ip_address) {
    while (true) {
        Transmitters::state(state, otherPlayers, PORT, my_ip_address, &my_socket);
        std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}


int main(int argc, char *argv[]) {

    options_description desc("Game options");
    desc.add_options()
        ("help", "produce help message")
        ("gamemode,g", value<std::string>(), "'single' for single player or 'multi' for multiplayer")
        ("ip,i", value<std::string>(), "your public IPv4 address")
        ("playermode,p", value<std::string>(), "'host' or 'client'")
        ("nclients,n", value<int>(), "number of clients that will join the game")
        ("hostip,h", value<std::string>(), "IPv4 address of the host")
    ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help")) {
        std::cout << desc << std::endl;
        return 0;
    }

    // time control variable
    std::chrono::duration<double> elapsed;

    // sdl events
    SDL_Event event;

    std::string my_ip_address = "127.0.0.1";
    bool isMultiplayer = vm.count("gamemode") ? vm["gamemode"].as<std::string>() == "multi" : false;
    bool isHost = false;

    // setup multiplayer
    if (isMultiplayer) {

        // get player's public ip address
        if (vm.count("ip")) {
            my_ip_address = vm["ip"].as<std::string>();
        } else {
            std::cout << "ERROR: Missing \"ip\" option!" << std::endl;
            std::cout << desc << std::endl;
            return 0;
        }

        // choose whether to join or create a game
        if (vm.count("playermode")) {
            isHost = vm["playermode"].as<std::string>() == "host";
        } else {
            std::cout << "ERROR: Missing \"playermode\" option!" << std::endl;
            std::cout << desc << std::endl;
            return 0;
        }

        // host: wait for players to join
        if (isHost) {

            //
            int nClients;
            if (vm.count("nclients")) {
                nClients = vm["nclients"].as<int>();
            } else {
                std::cout << "ERROR: Missing \"nclients\" option!" << std::endl;
                std::cout << desc << std::endl;
                return 0;
            }

            std::cout << "Waiting for players to join..." << std::endl;

            Receivers::handshakes(nClients, &otherPlayers, &my_socket, remote_endpoint, MAX_STATE_SIZE);

            Transmitters::otherPlayers(otherPlayers, PORT, &my_socket);

            std::cout << "Iniciando jogo!" << std::endl;

        // not a host: receive host ip and try to handshake
        } else {

            std::string hostIP;
            if (vm.count("hostip")) {
                hostIP = vm["hostip"].as<std::string>();
            } else {
                std::cout << "ERROR: Missing \"hostip\" option!" << std::endl;
                std::cout << desc << std::endl;
                return 0;
            }
            otherPlayers.push_back(hostIP);

            Transmitters::handshake(hostIP, "Can I join your game?", PORT, &my_socket, remote_endpoint, MAX_STATE_SIZE);
            Receivers::otherPlayers(&otherPlayers, my_ip_address, &my_socket, remote_endpoint, MAX_STATE_SIZE);
        }

        // create reception and transmission threads
        std::thread receptionThread(Receivers::state, &state, otherPlayers, &my_socket, remote_endpoint, MAX_STATE_SIZE);
        std::thread transmissionThread(transmitState, my_ip_address);

        //
        receptionThread.detach();
        transmissionThread.detach();
    }

    // game controller
    Controllers::Game game;
    game.isHost = isHost;
    game.isMultiplayer = isMultiplayer;
    game.my_ip_address = my_ip_address;

    // Game must run until user quits
    while (true) {

        // fetch start of game iteration
        auto start = std::chrono::system_clock::now();

        // Poll events
        if (SDL_PollEvent(&event)) {

            // User asked to quit: quit
            if (event.type == SDL_QUIT)
                break;

        }

        // update game state
        game.update(state, otherPlayers);

        // fetch end of game iteration
        auto end = std::chrono::system_clock::now();

        // measure time duration of game iteration
        elapsed = end - start;

        // control FPS
        SDL_Delay(35 - elapsed.count());

    }

    return 0;
}

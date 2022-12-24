
#include <iostream>
#include <string>
#include <boost/asio.hpp>


using boost::asio::ip::udp;

int main() {
  std::string v("{\"otherPlayers\": [\"127.0.0.1\"]}o");

  boost::asio::io_service io_service;

  udp::endpoint local_endpoint(udp::v4(), 0);
  udp::socket meu_socket(io_service, local_endpoint);


  // Encontrando IP remoto
  boost::asio::ip::address ip_remoto =
    boost::asio::ip::address::from_string("127.0.0.1");

  udp::endpoint remote_endpoint(ip_remoto, 5000);

  meu_socket.send_to(boost::asio::buffer(v), remote_endpoint);

  std::cout << v << std::endl;
  std::cout << "Fim" << std::endl;

  return 0;
}

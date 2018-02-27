// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898452045)
//
// Main routine for server program.
// This simple server is a console application only. Adopted from example at:
// http://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/tutorial/tutdaytime2/src.html.
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  boost::asio::io_service ioService;

  tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 666));

  while(1) {
    tcp::socket socket(ioService);
    acceptor.accept(socket);

    tcp::endpoint remoteHost(socket.remote_endpoint());
    std::cout << "Accepted a new incoming connection from "
	      << remoteHost.address().to_string() << std::endl;
  }

  return(0);
}

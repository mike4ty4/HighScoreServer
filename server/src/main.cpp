// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901383312)
//
// Main routine for server program.
// This is the full server program. (or will be when finished)
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  boost::asio::io_service ioService;

  tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 666));

  // NOTE: In this crude form the server will only accept one connection at a
  // time!
  while(1) {
    tcp::socket socket(ioService);
    acceptor.accept(socket);

    tcp::endpoint remoteHost(socket.remote_endpoint());
    std::cout << "Accepted a new incoming connection from "
	      << remoteHost.address().to_string() << std::endl;

    // Get input from this TCP connection.
    boost::system::error_code err;
    do {
      // Read in and stream all incoming input to the screen.
      boost::array<char, 128> buf;
      std::size_t len(socket.read_some(boost::asio::buffer(buf),
				       err));
      std::string str;
      std::copy(buf.begin(), buf.begin() + len, std::back_inserter(str));
      if(len > 0) {
	std::cout << str << std::endl;
      }
    } while(err != boost::asio::error::eof);

    std::cout << "Connection dropped." << std::endl;
  }

  return(0);
}

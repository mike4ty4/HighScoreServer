// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-03-20 (TAI: 1900232473)
//
// Main routine for client program.
// This simple server is a console application only. Adopted from example at:
// http://www.boost.org/doc/libs/1_66_0/doc/html/boost_asio/tutorial/tutdaytime2/src.html.
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  // Check for the right number of arguments.
  if (argc-1 != 1) {
    std::cout << "USAGE: consoleclient <server IP address>" << std::endl;
    return 1; // failed!
  }

  // Try to connect to the server.
  boost::asio::io_service ioService;
  tcp::resolver resolver(ioService);
  tcp::resolver::query query(argv[1], "666"); // server is on port 666
  tcp::resolver::iterator it(resolver.resolve(query));
  tcp::socket socket(ioService);

  if (boost::asio::connect(socket, it) == tcp::resolver::iterator()) {
    return(false); // connection failure
  }
  else {
    return(true); // connection successful
  }

  return 0;
}


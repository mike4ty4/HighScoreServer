// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898447099)
//
// Client communicator class implementation file.
// Adopted from example at:
// http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/tutorial/tutdaytime1/src.html
#include "inc/MMClient.h"
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

// Default constructor
MMClient::MMClient() {
}

// Connect to the server.
bool MMClient::connectToServer(std::string cServerIP) {
  boost::asio::io_service ioService;
  tcp::resolver resolver(ioService);
  tcp::resolver::query query(cServerIP, "666"); // server is on port 666
  tcp::resolver::iterator it(resolver.resolve(query));
  tcp::socket socket(ioService);

  if(boost::asio::connect(socket, it) == tcp::resolver::iterator()) {
    return(false); // connection failure
  } else {
    return(true); // connection successful
  }
}

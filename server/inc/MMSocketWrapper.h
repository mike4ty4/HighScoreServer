#ifndef MMSOCKETWRAPPER_H
#define MMSOCKETWRAPPER_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903433850)
//
// Declarations for the socket wrapper class (MMSocketWrapper). This is just to
// split off and wrap up some low-level data transfer functionality for
// receiving data from the client.
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/array.hpp>

// The class definition.
class MMSocketWrapper {
 private:
  boost::asio::io_service *ioService;
  boost::asio::ip::tcp::acceptor acceptor;
  
  boost::asio::ip::tcp::socket *socket;

  // Private function to receive bytes from the network socket.
  std::string receiveBytes(std::size_t nBytes);
 public:
  MMSocketWrapper(boost::asio::io_service *ioService_);

  // These socket routines should be self-explanatory by their names.
  bool connect();
  bool disconnect();

  // Receive a properly-formatted string input from the client. Such a string
  // input consists of a 10-digit (padded with leading zeros) ASCII decimal
  // length field giving the number of characters, followed by that many
  // characters for the string itself.
  std::string receiveString();
};

#endif // MMSOCKETWRAPPER_H

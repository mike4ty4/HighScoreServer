// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901347704)
//
// Implementation of the main class (MMClient) for the client program.
#include "MMClient.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace boost::asio;
using namespace boost::asio::ip;

// Private member: Write a string to the server. This is meant to be used
// in a chain with the error code containing that from a previous write, and
// so it also reads the error code as well as setting it and if this routine
// receives an error code that is not E_SUCCESS, it will refuse to do this
// write and instead allow the error to propagate by remaining in that
// variable.
void MMClient::writeStringToServer(std::string writeStr, int &e) {
  if(e == E_SUCCESS) {
    std::cout << "   INT: writing string '" << writeStr << "'" << std::endl;
    // In order to ensure this write is cleanly demarcated from successive
    // strings, we must first send the length of the string that will be coming
    // next.
    std::stringstream ssLength;
    ssLength << std::setfill('0') << std::setw(10) << writeStr.size();
    std::string lenStr(ssLength.str());
    write(socket, buffer(lenStr)); // always 10 bytes
    write(socket, buffer(writeStr)); // the actual string itself
  }
}

// Default constructor.
MMClient::MMClient()
  : ioService(),
    socket(ioService)
{
}

// Connect to server.
void MMClient::connect(std::string serverAddress, int &e) {
  // Attempt to resolve the server and connect to the socket.
  // The server is on port 666. Try to resolve this address.
  e = E_SUCCESS;
  
  tcp::resolver resolver(ioService);
  tcp::resolver::query query(serverAddress.c_str(), "666");
  tcp::resolver::iterator it(resolver.resolve(query));
  tcp::resolver::iterator end;
  if(it == end) {
    e = E_SERVER_NOT_FOUND;
  } else {
    try {
      boost::asio::connect(socket, it);
    } catch(const boost::system::system_error &exc) {
      e = E_CONNECTION_FAILURE;
    }
  }
}

// Disconnect from server.
void MMClient::disconnect(int &e) {
  boost::system::error_code rv;
  socket.shutdown(tcp::socket::shutdown_both, rv);
  if(rv) {
    e = E_DISCONNECT_FAILED;
  } else {
    e = E_SUCCESS;
  }
}

// Send a high score to the server.
void MMClient::sendHighScore(std::string gameID, std::string playerName, 
			     std::string score, int &e) {
  // Wrap the scores into a suitable format to send to the server.
  e = E_SUCCESS;
  writeStringToServer("NEWENT", e);
  writeStringToServer("GID", e);
  writeStringToServer(gameID, e);
  writeStringToServer("PNAME", e);
  writeStringToServer(playerName, e);
  writeStringToServer("SCORE", e);
  writeStringToServer(score, e);
  writeStringToServer("ENDENT", e);
}

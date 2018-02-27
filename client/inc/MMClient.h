#ifndef MMCLIENT_H
#define MMCLIENT_H

// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898446830)
//
// Client communicator object class declaration file.
#include <string>

// The client itself. This is based on BOOST apio.
class MMClient {
 private:
 public:
  MMClient(); // Default constructor
  bool connectToServer(std::string cServerIP); // Connect to the server.
};

#endif // MMCLIENT_H

// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901346046)
//
// Main routine for client program. This is the full client program which will
// be ready for use, unlike the prototype in previous commits.
#include "MMClient.h"
#include <iostream>
#include <chrono>

int main(int argc, char **argv) {
  // Sanity check to see if we got enough arguments.
  if(argc != 5) {
    std::cout << "USAGE: " << argv[0] << " <server hostname> <game ID> <player name> <score>" << std::endl;
    std::cout << std::endl;
    std::cout << "COMMAND-LINE INVOCATION EXAMPLE: " << std::endl;
    std::cout << argv[0] << " 127.0.0.1 0 \"Sikozu Shanu\" 9000" << std::endl;
    std::cout << std::endl;
    std::cout << "WINDOWS C/C++ INVOCATION EXAMPLE:" << std::endl;
    std::cout << "int result = system(\"cmd /c " << argv[0] << " 127.0.0.1 0 \\\"Sikozu Shanu\\\" 9000);" << std::endl;
    return(1); // bad args
  } else {
    // Create the client object and attempt to connect to the server.
    MMClient client;
    int errCode;
    client.connect(argv[1], errCode);
    if(errCode != MMClient::E_SUCCESS) {
      std::cout << "ERROR: Unable to connect to high-score server '"
		<< argv[1] << "'!" << std::endl;
      std::cout << "The client will now close." << std::endl;
      return(2); // connection failure
    }

    // Send to the server the data given in the remaining command-line
    // arguments for the high score entry.
    client.sendHighScore(argv[2], argv[3], argv[4], errCode);
    if(errCode != MMClient::E_SUCCESS) {
      std::cout << "ERROR: Failed to send score to server!" << std::endl;
    }

    client.disconnect(errCode);
  }
  
  return(0);
}

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

#include "MMLogger.h"
#include "MMSocketWrapper.h"
#include "MMServerModel.h"
#include "MMAsciiArtServerView.h"
#include "MMServerController.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  boost::asio::io_service ioService;

  // Set up server MVC pattern.
  MMServerModel serverModel;
  MMAsciiArtServerView serverView;
  MMServerController serverController;

  serverController.setModel(&serverModel);
  serverController.setView(&serverView);

  // Add games.
  serverController.prepareNewGame(1, "Dinosaur Hunter");
  serverController.prepareNewGame(2, "Sad Pancake");
  serverController.prepareNewGame(3, "Fish & Chips");
  serverController.prepareNewGame(4, "Space Shooter");
  serverController.prepareNewGame(5, "QFTDE 2");

  // Now handle input.
  MMSocketWrapper sockWrap(&ioService);
  while(1) {
    // Accept a connection.
    sockWrap.connect();

    // Get the commands.
    while(1) {
      std::string netInStr;
      if((netInStr = sockWrap.receiveString()) == "NEWENT") {
	serverController.startNewEntry();
      } else if((netInStr = sockWrap.receiveString()) == "GID") {
	serverController.receiveGameID(sockWrap.receiveString());
      } else if((netInStr = sockWrap.receiveString()) == "PNAME") {
	serverController.receivePlayerName(sockWrap.receiveString());
      } else if((netInStr = sockWrap.receiveString()) == "SCORE") {
	serverController.receiveScore(sockWrap.receiveString());
      } else if((netInStr = sockWrap.receiveString()) == "ENDENT") {
	serverController.endEntry();
	break;
      }
    }

    sockWrap.disconnect();
  }
  
  return(0);
}

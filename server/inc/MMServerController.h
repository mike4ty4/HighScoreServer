#ifndef MMSERVERCONTROLLER_H
#define MMSERVERCONTROLLER_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903431489)
//
// Declarations for the high score server controller class
// (MMServerController). This was formerly called MMServerInterface, but
// renamed to better fit with the MVC terminology. It has also been
// significantly revised since the original design together with better
// understanding of the MVC pattern.
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "MMServerModel.h"
#include "MMServerView.h"

// The class definition.
class MMServerController {
 private:
  MMServerModel *model;
  MMServerView *view;
  std::string gameIDBuf, playerNameBuf, scoreBuf;
 public:
  MMServerController(); // Default constructor

  // The functions, as with the Model, are again, rather updated since the
  // initial design. In this case they are designed to provide an interface
  // which better reflects the purpose of the Controller as responding to
  // external - in particular - network - events. There is also a function to
  // set the Model that will be used by this given Controller instance which
  // was not specified in the original class diagrams but is argued to be
  // implied by the association. Again, names and arguments should be self-
  // explanatory.
  void setModel(MMServerModel *newModel);
  void setView(MMServerView *newView);

  // Register a new game in the model.
  void prepareNewGame(int gameID, std::string gameName);
  
  // Begin a new score entry.
  void startNewEntry();

  // Receive the game ID for the score entry.
  void receiveGameID(std::string gameID);

  // Receive the player name for the score entry.
  void receivePlayerName(std::string playerName);

  // Receive the score for the score entry.
  void receiveScore(std::string score);

  // Finalize the score entry and enter into the model.
  void endEntry();

  // Send a game score to the model. This routine is only included to serve as
  // a delegate for example purposes; strictly speaking it would not be
  // necessary with the above routine which would call the necessary
  // functionality directly.
  void sendGameScoreDelegate(int gameID, std::string playerName, int score);
};

#endif // MMSERVERCONTROLLER_H

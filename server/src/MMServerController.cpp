// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903433688)
//
// Server controller class implementation.
#include "MMServerController.h"

// Default constructor
MMServerController::MMServerController()
  : model(NULL)
{
}

// Set the current server model.
void MMServerController::setModel(MMServerModel *newModel) {
  model = newModel;
}

// Set the current server view.
void MMServerController::setView(MMServerView *newView) {
  view = newView;
}

// Register a new game in the model.
void MMServerController::prepareNewGame(int gameID, std::string gameName) {
  model->addGame(gameID, gameName);
  view->addGameView(gameID, gameName);
}

// Begin a new score entry.
void MMServerController::startNewEntry() {
  gameIDBuf = ""; playerNameBuf = ""; scoreBuf = "";
}

// Receive the game ID for the score entry.
void MMServerController::receiveGameID(std::string gameID) {
  gameIDBuf = gameID;
}

// Receive the player name for the score entry.
void MMServerController::receivePlayerName(std::string playerName) {
  playerNameBuf = playerName;
}

// Receive the score for the score entry.
void MMServerController::receiveScore(std::string score) {
  scoreBuf = score;
}

// Finalize the score entry and enter into the model.
void MMServerController::endEntry() {
  char *end;
  int gameID = std::strtol(gameIDBuf.c_str(), &end, 10);
  int score = std::strtol(scoreBuf.c_str(), &end, 10);
  sendGameScoreDelegate(gameID, playerNameBuf, score);

  // Update the view to reflect the changes.
  MMServerModel::HighScoreVector hsv;
  model->getHiScores(gameID, 5, hsv);
  view->updateGameView(gameID, hsv);
}

// Send a game score to the model. (Delegate)
void MMServerController::sendGameScoreDelegate(int gameID,
					       std::string playerName,
					       int score) {
  model->insertScore(gameID, playerName, score);
}

#ifndef MMSERVERVIEW_H
#define MMSERVERVIEW_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903431289)
//
// Declarations for the high score server view class (MMServerView). This is
// basically just an abstract interface class, so there is not much in this
// file alone since we override it to create specific types of views for the
// model.
#include <string>
#include <vector>

// The class definition.
class MMServerView {
 public:
  virtual void addGameView(int gameID, std::string gameName) = 0;
  virtual void updateGameView(int gameID,
			      std::vector< std::pair<std::string, int> >
			      scoreList) = 0;
};

#endif // MMSERVERVIEW_H

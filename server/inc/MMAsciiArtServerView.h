#ifndef MMASCIIARTSERVERVIEW_H
#define MMASCIIARTSERVERVIEW_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903437590)
//
// Declarations for the ASCII art high score server view class
// (MMAsciiArtServerView). This is a specific implementation of the view for an
// ASCII art display. This is implemented using NCurses and ncurses windows.
#include <string>
#include <vector>
#include <map>

#include <curses.h>

#include "MMServerView.h"

// The class definition.
class MMAsciiArtServerView : public MMServerView {
 private:
  WINDOW *titleWindow;
  int curViewY, curViewX;
  
  std::map<int, std::string> gameNames;
  std::map<int, WINDOW *> gameWindows;
 public:
  MMAsciiArtServerView();
  ~MMAsciiArtServerView();
  
  void addGameView(int gameID, std::string gameName);
  void updateGameView(int gameID,
		      std::vector< std::pair<std::string, int> >
		      scoreList);
};

#endif // MMASCIIARTSERVERVIEW_H

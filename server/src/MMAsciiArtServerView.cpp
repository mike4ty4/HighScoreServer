// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903438029)
//
// ASCII art server view class implementation.
#include "MMAsciiArtServerView.h"
#include <locale.h>

// Default constructor
MMAsciiArtServerView::MMAsciiArtServerView() {
  // Initialize the ncurses system.
  setlocale(LC_CTYPE, "en_US.UTF-8");
  initscr();
  noecho();
  keypad(stdscr, TRUE);
  clear();
  refresh();

  // Create the window for the high score header.
  titleWindow = newwin(6, 80, 0, 0);
  wmove(titleWindow, 0, 0);
  waddstr(titleWindow, "█   █ █████  █████ █   █    █████ █████ █████ █████  █████ █████\n");
  waddstr(titleWindow, "█   █   █    █     █   █    █     █   █ █   █ █   █  █     █  \n");
  waddstr(titleWindow, "█████   █    █ ███ █████    █████ █     █   █ ████   ███   █████\n");
  waddstr(titleWindow, "█   █   █    █   █ █   █        █ █   █ █   █ █   █  █         █\n");
  waddstr(titleWindow, "█   █ █████  █████ █   █    █████ █████ █████ █   █  █████ █████\n");
  wrefresh(titleWindow);

  curViewY = 6;
  curViewX = 0;
}

// Destructor
MMAsciiArtServerView::~MMAsciiArtServerView() {
  endwin();
}

// Add a game view.
void MMAsciiArtServerView::addGameView(int gameID, std::string gameName) {
  // Add the name for this game.
  gameNames[gameID] = gameName;
  
  // Create a new view for this game.
  gameWindows[gameID] = newwin(7, 25, curViewY, curViewX);
  curViewX += 25;
  if(curViewX + 25 > 80) {
    curViewX = 0;
    curViewY += 7;
  }

  // Update the window.
  wrefresh(gameWindows[gameID]);
}

// Update a game view.
void MMAsciiArtServerView::updateGameView(int gameID,
					  std::vector< std::pair<std::string, int> > scoreList) {
  // Clear the window.
  wclear(gameWindows[gameID]);

  // Now write the scores to the window.
  wmove(gameWindows[gameID], 0, 0);
  waddstr(gameWindows[gameID], gameNames[gameID].c_str());

  int yCoord = 1;
  for(std::vector< std::pair<std::string, int> >::iterator it(scoreList.begin());
      it != scoreList.end();
      ++it) {
    // Write name
    wmove(gameWindows[gameID], yCoord, 0);
    waddstr(gameWindows[gameID], it->first.c_str());

    // Write score
    wmove(gameWindows[gameID], yCoord, 15);
    std::string scoreStr(std::to_string(it->second));
    waddstr(gameWindows[gameID], scoreStr.c_str());

    // Go to next row
    ++yCoord;
  }

  // Update the window.
  wrefresh(gameWindows[gameID]);
}

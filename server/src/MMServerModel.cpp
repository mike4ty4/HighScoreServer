// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-25 (TAI: 1903406440)
//
// Server model class implementation.
#include "MMServerModel.h"

// Add a new game entry to the server model. The game name passed must be a
// nonempty string.
// Returns:
//      E_SUCCESS - no error
//      E_GAME_ID_ALREADY_IN_USE - tried to use an existing game ID
//      E_INVALID_GAME_NAME - tried using an empty string as the game name.
int MMServerModel::addGame(int gameID, std::string gameName) {
  if(nameContainer.find(gameID) != nameContainer.end()) {
    return(E_GAME_ID_ALREADY_IN_USE);
  } else {
    if(gameName.size() == 0) {
      return(E_INVALID_GAME_NAME);
    } else {
      nameContainer[gameID] = gameName;
      scoreContainer[gameID] = ScoreList();

      return(E_SUCCESS);
    }
  }
}

// Get a game name from the server model. If the game is not found, returns an
// empty string.
std::string MMServerModel::getGameName(int gameID) {
  if(nameContainer.find(gameID) == nameContainer.end()) {
    return(""); // game ID not found
  } else {
    return(nameContainer[gameID]);
  }
}

// Insert a new high score into the server model.
// Returns:
//      E_SUCCESS - no error
//      E_INVALID_GAME_ID - game ID does not correspond to an existing game.
int MMServerModel::insertScore(int gameID, std::string playerName,
			       int score) {
  if(nameContainer.find(gameID) == nameContainer.end()) {
    return(E_INVALID_GAME_ID); // game ID not found
  } else {
    // We need to check if there are any existing entries for this game which
    // already have this player name, since we will want to overwrite them
    // instead of having a duplicate score entry for the same player. (Although
    // perhaps, this could be desired behavior, e.g. two plays with same player
    // to compare highest scores? Not sure about this.)
    std::map<int, ScoreList>::iterator it(scoreContainer.find(gameID));
    for(ScoreList::iterator itl(it->second.begin());
	itl != it->second.end();
	++itl) {
      if(itl->second == playerName) {
	it->second.erase(itl);
	break;
      }
    }

    // Now insert the entry.
    it->second.insert(ScoreKey(score, playerName));

    // Done!
    return(E_SUCCESS);
  }
}

// Get the top N (numToGet) highest scores for a given game. If N exceeds the
// total contained, return all the scores.
// Returns:
//      E_SUCCESS - no error
//      E_INVALID_GAME_ID - game ID does not correspond to an existing game.
int MMServerModel::getHiScores(int gameID, int numToGet,
			       HighScoreVector &vec) {
  if(nameContainer.find(gameID) == nameContainer.end()) {
    return(E_INVALID_GAME_ID); // game not found
  } else {
    vec.clear(); // Prepare output vector to receive scores.
    std::map<int, ScoreList>::iterator it(scoreContainer.find(gameID));
    ScoreList::iterator scoreIt(it->second.begin());
    for(int i(0); i < numToGet; ++i) {
      // Bail out of the loop if we have already gotten all the scores on the
      // list.
      if(scoreIt == it->second.end()) {
	break;
      }

      // Otherwise, add the score to the growing output vector.
      vec.push_back(std::pair<std::string, int>(scoreIt->second,
						scoreIt->first));
      ++scoreIt;
    }

    return(E_SUCCESS);
  }
}

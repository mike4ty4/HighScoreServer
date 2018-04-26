#ifndef MMSERVERMODEL_H
#define MMSERVERMODEL_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-25 (TAI: 1903403599)
//
// Declarations for the high score server model class (MMServerModel). This is
// one part of a tripartite MVC (Model-View-Controller) pattern setup for
// internally structuring this server program. The server model class holds
// all the score data as well as keeping it sorted in numerical order from high
// to low and permitting both storage of new scores and retrieval of lists of
// existing scores. Games are referenced by their game ID number, not a game
// name (so this is not quite the same as in the submitted class diagram in the
// client/doc folder, as the use of a game ID to refer to the game was a
// newfangled feature that was not part of the original spec but decided upon
// later in consultation with *BEESTON*.), although the class does also store
// game names.
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>

// The class definition.
class MMServerModel {
 private:
  // The data is stored in a series of parallel associative containers. One
  // container stores the game names, the other stores the associated list of
  // scores. This is done because while in a production program a simple POD
  // struct for each game would probably be nicer and more efficient, we are
  // FORBIDDEN from using POD structs in this coursework project. Also, due to
  // this same requirement, we are forbidden even to use a small POD struct
  // with labeled elements to more clearly store the pairing of scores together
  // with the associated player name and instead use an std::pair - which also
  // gives us a comparison operator for free (std::less and std::greater) and
  // is why we put the int part, for the score, before the string poart, for
  // the player name, since the first element is compared before the second and
  // this ensures the scores are always sorted by the score value and not by
  // the alphabetical lex ordering of the player names. std::set is used
  // because it is a sorted container.
  typedef std::pair<int, std::string> ScoreKey;
  typedef std::set< ScoreKey, std::greater<ScoreKey> > ScoreList;
  
  std::map<int, std::string> nameContainer;
  std::map<int, ScoreList> scoreContainer;
 public:
  // Error codes.
  enum {
    E_SUCCESS,
    E_GAME_ID_ALREADY_IN_USE,
    E_INVALID_GAME_NAME,
    E_INVALID_GAME_ID
  };

  typedef std::vector< std::pair<std::string, int> > HighScoreVector;

  // There are fewer methods here than in the original class diagram. This
  // author realized it would be simpler ("KISS" principle) to just have it so
  // that there is no need to keep a "player" as a separate construct since
  // it's just a name paired with score, and it's more natural to just insert a
  // score entry with player's name and score than to go through a complex
  // procedure of inserting a player, before that checking for the player if it
  // already exists, and only then adding scores. Not sure if this kind of
  // revision is okay or not or what the rules concerning such revisions are
  // since there's no further class diagram submissions required. Purpose of
  // routines should be self-evident from names. Meh, this is already at
  // variance with the class diagram given we are using game IDs instead of
  // game names as handles...
  int addGame(int gameID, std::string gameName);
  std::string getGameName(int gameID);
  int insertScore(int gameID, std::string playerName, int score);
  int getHiScores(int gameID, int numToGet, HighScoreVector &vec);
};

#endif // MMSERVERMODEL_H

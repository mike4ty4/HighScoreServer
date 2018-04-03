// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901347779)
//
// Declarations for the main class (MMClient) of the client program.
// This class is used internally within the client executable: it is NOT
// the one that is linked to user programs to communicate with the client
// program.
#include <string>
#include <boost/asio.hpp>

// The class definition.
class MMClient {
 public:
  // Error codes.
  enum {
    E_SUCCESS,
    E_SERVER_NOT_FOUND,
    E_CONNECTION_FAILURE,
    E_CONNECTION_DROPPED,
    E_DISCONNECT_FAILED
  };
 private:
  // Connection internals.
  boost::asio::io_service ioService; // The Boost IO service object.
  boost::asio::ip::tcp::socket socket; // The socket to connect with.

  // Write a string to the server.
  void writeStringToServer(std::string server, int &e);
 public:
  // Default constructor.
  // Parameters:
  //    None.
  MMClient();
  
  // Connect to server.
  // Parameters:
  //    serverAddress: IP address or DNS name of the server.
  //    e: Error code return.
  void connect(std::string serverAddress, int &e); // Connect to server.

  // Disconnect from server.
  // Parameters:
  //    e: Error code return.
  void disconnect(int &e); // Disconnect from server.

  // Send a high score to the server.
  // Parameters:
  //    gameID: The ID code of the game.
  //    playerName: The name of the player.
  //    score: The high score entry for this player.
  //    e: Error code return.
  void sendHighScore(std::string gameID, std::string playerName, 
		     std::string score,
		     int &e); // Send a high score value.
};

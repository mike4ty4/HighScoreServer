// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901346046)
//
// Main routine for client program. This is the full client program which will
// be ready for use, unlike the prototype in previous commits.
#include "MMClient.h"
#include "MMSharedMemory.h"
#include <iostream>
#include <chrono>
/*
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>
*/

int main(int argc, char **argv) {
  // Sanity check to see if we got enough arguments.
  if(argc != 2) {
    std::cout << "USAGE: hssclient <server IP address/URL>" << std::endl;
    return(1); // bad args
  } else {
    // Set up a shared memory area to be used for communicating with client
    // games.
    MMSharedMemory sharedMem("hss_shared_mem", 1024);
    
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

    sharedMem.writeReq("READY", "");
    
    // Wait for requests in the shared memory and send them to the server.
    while(1) {
      if(sharedMem.waitForAnyReq() == "COMMAND") {
	sharedMem.writeReq("ACK", "");
	std::string cmd(sharedMem.waitForAnyReq());
	if(cmd == "NEWSCORE") {
	  std::cout << "HSS CLIENT: Got new score dispatch request!" << std::endl;
	  sharedMem.writeReq("ACK", "");
	  
	  // We have a new score request coming in.
	  std::string playerName, gameName, score;
	  sharedMem.waitForReq("PNAME");
	  {
	    std::cout << "HSS CLIENT: Got player name" << std::endl;
	    playerName = sharedMem.getReqParam();
	    sharedMem.writeReq("ACK", "");
	  }

	  sharedMem.waitForReq("GNAME");
	  {
	    std::cout << "HSS CLIENT: Got game name" << std::endl;
	    gameName = sharedMem.getReqParam();
	    sharedMem.writeReq("ACK", "");
	  }

	  sharedMem.waitForReq("SCORE");
	  {
	    std::cout << "HSS CLIENT: Got score" << std::endl;
	    score = sharedMem.getReqParam();
	    sharedMem.writeReq("ACK", "");
	  }

	  // Send it to the server!
	  std::cout << "HSS CLIENT: Sending score to server..." << std::endl;
	  client.sendHighScore(playerName, gameName, score, errCode);
	  if(errCode != MMClient::E_SUCCESS) {
	    std::cout << "ERROR: Failed to send score to server!" << std::endl;
	  }
	} else if(cmd == "QUIT") {
	  std::cout << "HSS CLIENT: Got quit command!" << std::endl;
	  sharedMem.writeReq("ACK", "");
	  break;
	}
      }

      sharedMem.writeReq("READY", "");
    }

    client.disconnect(errCode);
  }
  
  return(0);
}

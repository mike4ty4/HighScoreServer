// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901383525)
//
// Automatic tester for client program. This simulates a "game" attached to the
// client. This must be run only with the client already running!
#include <iostream>
#include "MMSharedMemory.h"

int main(int argc, char **argv) {
  MMSharedMemory sharedMem("hss_shared_mem");
  
  sharedMem.writeReq("COMMAND", "");
  sharedMem.waitForReq("ACK");
  sharedMem.writeReq("NEWSCORE", "");
  sharedMem.waitForReq("ACK");
  sharedMem.writeReq("PNAME", "Sikozu");
  sharedMem.waitForReq("ACK");
  sharedMem.writeReq("GNAME", "The Ganing 2");
  sharedMem.waitForReq("ACK");
  sharedMem.writeReq("SCORE", "9000");
  sharedMem.waitForReq("ACK");

  return(0);
}

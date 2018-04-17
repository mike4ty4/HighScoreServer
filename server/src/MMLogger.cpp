// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1902635669)
//
// Server logging class implementation.
#include <iomanip>
#include <sys/time.h>

#include "MMLogger.h"

// The instance variable initialization.
MMLogger *MMLogger::instance = NULL;

// Private default constructor
MMLogger::MMLogger()
  : logFile("hss_server.log", std::ios::app)
{
  if(!logFile) {
    // Unable to create log file!
    std::cerr << "HSS ERROR: Unable to open log file 'hss_server.log'!" <<
      std::endl;
    std::cerr << "           Logging is disabled for this server session." <<
      std::endl;
  }
}

// Log an event to the event log.
void MMLogger::logEvent(std::string event) {
  std::string outStr;

  // Timestamp this event with UNIX metric time.
  std::stringstream ssTime;
  struct timeval tv;
  gettimeofday(&tv, NULL);
  ssTime << "[" << std::setfill(' ') << std::setw(10) << tv.tv_sec << "."
	 << std::setfill('0') << std::setw(6) << tv.tv_usec << "] ";

  // Create output string.
  outStr = ssTime.str() + event;

  // Write to the file.
  if(logFile) {
    logFile << outStr << std::endl;
  }
}

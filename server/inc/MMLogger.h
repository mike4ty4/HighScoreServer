#ifndef MMLOGGER_H
#define MMLOGGER_H
// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-16 (TAI: 1902635006)
//
// Declarations for the logger (MMLogger) to log server events. This is used
// mostly for troubleshooting, to make sure the requests are being
// received. In addition, a real server might need to keep a log for
// usage statistics or to aid the administrator in checking for possible
// security breaches.
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

// The class definition. This uses a singleton pattern because there should be
// only one logger for the whole program to log events from anywhere they may
// come.
class MMLogger {
 private:
  static MMLogger *instance; // The unique instance.

  std::ofstream logFile; // The log file.

  MMLogger(); // Private default constructor
 public:
  static MMLogger *getInstance() {
    if(instance == NULL) {
      instance = new MMLogger();
    }

    return(instance);
  }

  void logEvent(std::string event); // Log an event to the event log.
};

#endif // MMLOGGER_H

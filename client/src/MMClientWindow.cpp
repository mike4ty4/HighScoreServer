// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898443728)
//
// Client GUI window class implementation file.
#include "inc/MMClientWindow.h"
#include <QPushButton>

// Default constructor
MMClientWindow::MMClientWindow() {
  // Create the basic setup. For this prototype program, the setup consists
  // of a button to connect to the server and a button to message the server.
  // The IP address of the server is passed by command line (see main.cpp).
  this->resize(200, 200);
  this->setFixedSize(200, 200);

  cConnectButton = new QPushButton("&Connect", this);
  cConnectButton->move(QPoint(5, 5)); // give a little spacing between the
                                      // windows and buttons
  cTransmitButton = new QPushButton("&Transmit", this);
  cTransmitButton->move(cConnectButton->geometry().bottomLeft() +
			QPoint(0, 5)); // ditto
}

// Destructor
MMClientWindow::~MMClientWindow() {
}

#ifndef MMCLIENTWINDOW_H
#define MMCLIENTWINDOW_H

// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898443599)
//
// Client GUI window class declaration file.
#include <QMainWindow>

// The main GUI window class.
class QPushButton;

class MMClientWindow : public QMainWindow {
 private:
  QPushButton *cConnectButton, *cTransmitButton;
 public:
  MMClientWindow(); // Default constructor
  ~MMClientWindow(); 
};

#endif // MMCLIENTWINDOW_H

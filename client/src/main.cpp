// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-02-27 (TAI: 1898442866)
//
// Main routine for client program - called by QT
#include <QApplication>
#include "inc/MMClientWindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  
  MMClientWindow *cClientWindow = new MMClientWindow();
  cClientWindow->show();
  
  return(app.exec());
}

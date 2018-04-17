// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901383312)
//
// Main routine for server program.
// This is the full server program. (or will be when finished)
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/array.hpp>

#include "MMLogger.h"

using boost::asio::ip::tcp;

int main(int argc, char *argv[]) {
  boost::asio::io_service ioService;

  tcp::acceptor acceptor(ioService, tcp::endpoint(tcp::v4(), 666));

  // NOTE: In this crude form the server will only accept one connection at a
  // time!
  while(1) {
    tcp::socket socket(ioService);
    acceptor.accept(socket);

    tcp::endpoint remoteHost(socket.remote_endpoint());
    MMLogger::getInstance()->logEvent
      (std::string("Accepted a new incoming connection from: ") +
       remoteHost.address().to_string());

    // Get input from this TCP connection.
    boost::system::error_code err;
    do {
      // Read in and stream all incoming input to the screen.
      boost::array<char, 128> buf;

      // First, read the length of the following string.
      std::size_t len(boost::asio::read(socket, boost::asio::buffer(buf),
					boost::asio::transfer_exactly(10),
					err));
      if(len == 0) {
	// ignore empty reads
      } else if(len != 10) {
	MMLogger::getInstance()->logEvent
	  (std::string("Got malformed incoming string with bad length field! (got len ") +
	   std::to_string(len) + std::string(" of 10)"));
      } else {
	std::string readLenStr;
	std::copy(buf.begin(), buf.begin() + 10,
		  std::back_inserter(readLenStr));
	std::size_t lenVal(std::stoul(readLenStr));
	len = boost::asio::read(socket, boost::asio::buffer(buf),
				boost::asio::transfer_exactly(lenVal),
				err);
	if(len != lenVal) {
	  MMLogger::getInstance()->logEvent
	    ("Tried to read in string and was cut abruptly at length " +
	     std::to_string(len) + " out of " + std::to_string(lenVal));
	} else {
	  std::string str;
	  std::copy(buf.begin(), buf.begin() + len, std::back_inserter(str));
	  if(len > 0) {
	    MMLogger::getInstance()->logEvent("Got command \"" + str + "\"");
	  }
	}
      }
    } while(err != boost::asio::error::eof);

    MMLogger::getInstance()->logEvent("Connection dropped.");
  }

  return(0);
}

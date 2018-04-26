// CS 383 High Score Server System (HSS System) - Server Side
// Author: Michael Moldenhauer
// Date: 2018-04-26 (TAI: 1903434154)
//
// Socket wrapper class implementation.
#include "MMSocketWrapper.h"
#include "MMLogger.h"

using boost::asio::ip::tcp;

// Private function to receive bytes from the network socket. NOTE: limited to
// max 128 bytes read.
std::string MMSocketWrapper::receiveBytes(std::size_t nBytes) {
  // Clip too-long reads.
  if(nBytes > 128) {
    nBytes = 128;
    MMLogger::getInstance()->logEvent(std::string("requested read of too many bytes (got ") +
				      std::to_string(nBytes) + " which exceeds 128 max)");
  }

  // Now try to read it in.
  boost::system::error_code err;
  std::size_t len;
  do {
    boost::array<char, 128> buf;
    len = boost::asio::read((*socket), boost::asio::buffer(buf),
			    boost::asio::transfer_exactly(nBytes), err);
    if(len == 0) {
      // Ignore empty reads.
    } else if(len != nBytes) {
      MMLogger::getInstance()->logEvent(std::string("improper read of ") +
					std::to_string(len) +
					std::string("bytes while requesting read of ") +
					std::to_string(nBytes) + std::string(" bytes"));
      return(""); // Failure!
    } else {
      // Got it!
      std::string returnStr;
      std::copy(buf.begin(), buf.begin() + nBytes, std::back_inserter(returnStr));
      return(returnStr);
    }
  } while(err != boost::asio::error::eof);
}

// Default constructor
MMSocketWrapper::MMSocketWrapper(boost::asio::io_service *ioService_)
  : ioService(ioService_),
    acceptor(*ioService, tcp::endpoint(tcp::v4(), 666)),
    socket(NULL)
{
}
  
// Connect to a remote host requesting a connection using the given network
// context.
// Returns:
//      true if connected, false if failed (error will be logged)
bool MMSocketWrapper::connect() {
  // Perform the connection.
  socket = new tcp::socket(*ioService);
  acceptor.accept(*socket);

  // Log the address connected to.
  tcp::endpoint remoteHost(socket->remote_endpoint());
  MMLogger::getInstance()->logEvent(std::string("Accepted a new incoming connection from: ") +
				    remoteHost.address().to_string());

  return(true);
}

// Disconnect from the currently-connected host.
bool MMSocketWrapper::disconnect() {
  delete socket;
  socket = NULL;

  return(true);
}

// Receive a properly-formatted string input from the client.
std::string MMSocketWrapper::receiveString() {
  std::string lengthCode(receiveBytes(10));
  if(lengthCode.size() != 10) {
    MMLogger::getInstance()->logEvent(std::string("Got malformed incoming string with bad length field! (got len ") +
				      std::to_string(lengthCode.size()) +
				      std::string(" of 10)"));

    return(""); // failure
  } else {
    std::size_t lenVal(std::stoul(lengthCode));
    std::string inpStr(receiveBytes(lenVal));
    if(inpStr.size() != lenVal) {
      MMLogger::getInstance()->logEvent("Tried to read in string and was cut abruptly at length " +
					 std::to_string(inpStr.size()) + "out of " +
					 std::to_string(lenVal));
      return(""); // failure
    }

    return(inpStr);
  }
}

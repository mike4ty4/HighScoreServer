#ifndef MMSHAREDMEMORY_H
#define MMSHAREDMEMORY_H
// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901360836)
//
// Declarations for the shared memory class that wraps BOOST or another shared-
// memory interprocess communication system and is used to communicate between
// the games and the client program.
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

// The class definition.
class MMSharedMemory {
 private:
  std::string storedName;
  boost::interprocess::managed_shared_memory *msm;

  typedef boost::interprocess::managed_shared_memory::segment_manager
    IPCSegManager;
  typedef boost::interprocess::allocator<char, IPCSegManager> IPCCharAlloc;
  typedef boost::interprocess::basic_string
    <char, std::char_traits<char>, IPCCharAlloc> IPCString;

  IPCString *storedReqName, *storedReqParam;
 public:
  // Construct with a given name and size.
  // Parameters:
  //    segmentName: Name of shared memory segment.
  //    size: Size of the memory region to create.
  MMSharedMemory(std::string segmentName, std::size_t size);
  
  // Construct as a connection to an existing shared memory object created by
  // another program.
  // Parameters:
  //    segmentName: Name of shared memory segment.
  MMSharedMemory(std::string segmentName);

  // Destructor
  ~MMSharedMemory();

  // Write a requrest into the shared memory.
  // Parameters:
  //    reqName: Name of the request.
  //    reqParam: The request parameter.
  void writeReq(std::string reqName, std::string reqParam);

  // Read current request name from the shared memory.
  // Parameters:
  //    None.
  std::string getReqName();

  // Read current request parameters from the shared memory.
  // Parameters:
  //    None.
  std::string getReqParam();

  // Wait for a certain request to come in.
  // Parameters:
  //    reqName: Name of the request to wait for.
  void waitForReq(std::string reqName);

  // Wait for any change in request buffer. Returns the new request.
  // Parameters:
  //    None.
  std::string waitForAnyReq();
};

#endif // MMSHAREDMEMORY_H

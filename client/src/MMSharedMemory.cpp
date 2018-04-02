// CS 383 High Score Server System (HSS System) - Client Side
// Author: Michael Moldenhauer
// Date: 2018-04-02 (TAI: 1901362050)
//
// Implementation of the shared memory class (MMSharedMemory) using BOOST.
#include "MMSharedMemory.h"
#include <chrono>
#include <thread>

using namespace boost::interprocess;

// Construct with a given name and size.
MMSharedMemory::MMSharedMemory(std::string segmentName, std::size_t size)
  : storedName(segmentName),
    msm(NULL),
    storedReqName(NULL),
    storedReqParam(NULL)
{
  // Initialize the shared memory space.
  shared_memory_object::remove(storedName.c_str()); // must be done to clean up
                                                    // from previous program
                                                    // instances (!)
  msm = new managed_shared_memory(create_only, storedName.c_str(), size);
  
  // Prepare the string objects in this shared memory space.
  storedReqName = msm->construct<IPCString>("req_name_val")
    ("", msm->get_segment_manager());
  storedReqParam = msm->construct<IPCString>("req_param_val")
    ("", msm->get_segment_manager());
}

// Construct as a connection to an existing shared memory object created by
// another program.
MMSharedMemory::MMSharedMemory(std::string segmentName)
  : storedName(segmentName),
    msm(NULL),
    storedReqName(NULL),
    storedReqParam(NULL)
{
  msm = new managed_shared_memory(open_only, storedName.c_str());
  
  storedReqName = msm->find<IPCString>("req_name_val").first;
  storedReqParam = msm->find<IPCString>("req_param_val").first;
}

// Destructor
MMSharedMemory::~MMSharedMemory() {
  //shared_memory_object::remove(storedName.c_str());
  delete msm;
}

// Write a request into the shared memory.
void MMSharedMemory::writeReq(std::string reqName, std::string reqParam) {
  (*storedReqName) = reqName.c_str();
  (*storedReqParam) = reqParam.c_str();
}

// Read current request parameters from the shared memory.
std::string MMSharedMemory::getReqName() {
  return((*storedReqName).c_str());
}

// Read current request parameters from the shared memory.
std::string MMSharedMemory::getReqParam() {
  return((*storedReqParam).c_str());
}

// Wait for a certain request to come in.
void MMSharedMemory::waitForReq(std::string reqName) {
  using namespace std::chrono_literals;
  
  while(1) {
    std::string reqNameIn(getReqName());
    if(reqNameIn == reqName) {
      break;
    }

    std::this_thread::sleep_for(1ms);
  }
}

// Wait for any change in request buffer.
std::string MMSharedMemory::waitForAnyReq() {
  using namespace std::chrono_literals;
  
  std::string reqBuf(getReqName());
  while(1) {
    std::string reqNameIn(getReqName());
    if(reqNameIn != reqBuf) {
      return(reqNameIn);
    }

    std::this_thread::sleep_for(1ms);
  }
}

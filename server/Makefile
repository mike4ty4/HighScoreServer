# UNIX makefile for server.
# Created 2018-02-27 (TAI: 1898452579)
CC=gcc
CXX=g++
CXXFLAGS=-g --std=c++11 -I/home/manager/boost_1_66_0/ -I./inc
LDFLAGS=-L/home/manager/boost_1_66_0/stage/lib
LIBS=-lpthread -lncursesw
SRCS=src/MMLogger.cpp src/MMSocketWrapper.cpp src/MMServerModel.cpp src/MMServerController.cpp src/MMAsciiArtServerView.cpp src/main.cpp

hssserver: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) /home/manager/boost_1_66_0/stage/lib/libboost_system.a /home/manager/boost_1_66_0/stage/lib/libboost_thread.a -o hssserver $(LIBS)

# UNIX makefile for client.
# Created 2018-03-22 (TAI: 1900237197)
CC=gcc
CXX=g++
CXXFLAGS=-I/usr/local/boost_1_59_0/
LDFLAGS=-L/usr/local/boost_1_59_0/stage/lib
LIBS=-lpthread -lboost_thread -lboost_system
SRCS=src/main.cpp

hssclient: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o hssclient $(LIBS)

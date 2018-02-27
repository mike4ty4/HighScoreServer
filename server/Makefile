# UNIX makefile for server.
# Created 2018-02-27 (TAI: 1898452579)
CC=gcc
CXX=g++
CXXFLAGS=-I/usr/local/boost_1_59_0/
LDFLAGS=-L/usr/local/boost_1_59_0/stage/lib
LIBS=-lboost_system -lboost_thread
SRCS=src/main.cpp

hssserver: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o hssserver $(LIBS)

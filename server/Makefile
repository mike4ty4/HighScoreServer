# UNIX makefile for server.
# Created 2018-02-27 (TAI: 1898452579)
CC=gcc
CXX=g++
CXXFLAGS=-g --std=c++11 -static -I/home/manager/boost_1_66_0/ -I./inc
LDFLAGS=-L/home/manager/boost_1_66_0/stage/lib
LIBS=-lpthread -lboost_system -lboost_thread
SRCS=src/MMLogger.cpp src/main.cpp

hssserver: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o hssserver $(LIBS)

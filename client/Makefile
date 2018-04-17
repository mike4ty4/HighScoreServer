# UNIX makefile for client.
# Created 2018-03-22 (TAI: 1900237197)
CC=gcc
CXX=g++
CXXFLAGS=--std=c++11 -static -I/home/manager/boost_1_66_0/ -I./inc
LDFLAGS=-L/home/manager/boost_1_66_0/stage/lib
LIBS=-lpthread -lboost_system -lboost_thread
SRCS=src/MMClient.cpp src/main.cpp

hssclient: $(SRCS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(SRCS) -o hssclient $(LIBS)

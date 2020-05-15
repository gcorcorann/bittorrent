# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -I/usr/local/opt/openssl/include
LDFLAGS = -L/usr/local/opt/openssl/lib/
LDLIBS = -lcrypto

main: main.o
	$(CXX) $(CXXFLAGS) -o main main.o $(LDFLAGS) $(LDLIBS)

main.o: main.cpp binary.h decoder.h encoder.h tokenize.h value.h hash.h
	$(CXX) $(CXXFLAGS) -c main.cpp

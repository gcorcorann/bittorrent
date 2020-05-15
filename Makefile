# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -I/usr/local/opt/openssl/include -Iinclude/
LDFLAGS = -L/usr/local/opt/openssl/lib/
LDLIBS = -lcrypto

main: main.o
	$(CXX) $(CXXFLAGS) -o main.out main.o $(LDFLAGS) $(LDLIBS)

main.o: src/main.cpp include/binary.h include/decoder.h include/encoder.h include/tokenize.h include/value.h include/hash.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp

clean:
	rm -rf *o all

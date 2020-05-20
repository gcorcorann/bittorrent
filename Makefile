# Variables to control Makefile operation
CXX = g++
CXXFLAGS = -Wall -g -std=c++2a -I/usr/local/opt/openssl/include -Iinclude/
LDFLAGS = -L/usr/local/opt/openssl/lib/
LDLIBS = -lcrypto

main: main.o
	$(CXX) $(CXXFLAGS) -o main.out main.o $(LDFLAGS) $(LDLIBS)

main.o: src/main.cpp include/binary.h include/decoder.h include/encoder.h include/tokenize.h include/value.h include/hash.h include/request.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp

test_socket: objs/test_socket.o
	$(CXX) $(CXXFLAGS) -o bin/test_socket.out objs/test_socket.o

objs/test_socket.o: test/test_socket.cpp include/socket.h
	$(CXX) $(CXXFLAGS) -c test/test_socket.cpp -o objs/test_socket.o

test_request: objs/test_request.o
	$(CXX) $(CXXFLAGS) -o bin/test_request.out objs/test_request.o

objs/test_request.o: test/test_request.cpp include/request.h include/socket.h
	$(CXX) $(CXXFLAGS) -c test/test_request.cpp -o objs/test_request.o

clean:
	rm -rf *o all

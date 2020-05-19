#pragma once
#include <string>
#include <iostream>

#include <sys/socket.h>
#include <netdb.h>  // gethostbyname
#include <unistd.h>  // read

class Socket {
private:
    std::string m_hostname;
    unsigned short int m_port;

    /*
     * Returns pointer to an object with following structure describing an internet
     * host referenced by name.
     *
     * struct hostent {
     *      char *h_name:  // official host name
     *      char **h_aliases;  // alias list
     *      int h_addrtype;  // host address type
     *      int h_length;  // length of address
     *      char **h_addr_list;  // list of addresses from name sever
     */
    hostent* resolveHostname() {
        hostent* host = gethostbyname(m_hostname.c_str());
        if (host == nullptr || host->h_addr == nullptr) {
            throw std::invalid_argument("Hostname is not valid.");
        }
        return host;
    }

    int createTCP_Socket() {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            throw std::invalid_argument("Invalid socket");
        }
        return sock;
    }

    void connectServer(hostent host, int socket) {
        sockaddr_in serv_addr;
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(m_port);
        // copy n bytes from src to dst (memcpy(dst, src, n))
        memcpy(&serv_addr.sin_addr, host.h_addr, host.h_length);
        if (connect(socket, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            throw std::invalid_argument("Connection failed.");
        }
    }

public:
    Socket(std::string hostname) : m_hostname(hostname), m_port(80) { };

    Socket(std::string hostname, unsigned short int port)
        : m_hostname(hostname), m_port(port) { };

    void send_tcp(const char* message) {
        hostent* host = resolveHostname();
        int socket = createTCP_Socket();
        connectServer(*host, socket);
        send(socket, message, strlen(message), 0);
        char buffer[2024] = {0};
        read(socket, buffer, 2024);
        std::cout << buffer << std::endl;
    }

    void print() {
        std::cout << "Hostname: " << m_hostname << '\n';
        std::cout << "Port: " << m_port << '\n';
    }
};

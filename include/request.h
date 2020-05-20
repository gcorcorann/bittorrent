#pragma once
#include <string>
#include <iostream>

#include "socket.h"

class Request {
private:
    std::string m_host;
    std::string m_resource;
    Socket m_socket;
public:
    /*
     * set host and resource from announce
     */
    Request(std::string host, std::string resource, Socket socket)
        : m_host(host), m_resource(resource), m_socket(socket) {
        /*
        size_t pos = announce.rfind("/");
        if (pos != std::string::npos) {
            m_resource = announce.substr(pos, announce.size() - pos);
            m_host = announce.substr(0, pos);
        }
        else {
            throw std::invalid_argument("Accounce string incorrect format.");
        }
        m_port = port;
        m_socket = Socket(m_host.substr(0, m_host.size() - 5), port);
        */
    }

    void get(std::string info_hash) {
        std::string message = "GET " + m_resource + " HTTP/1.1\r\n";
        message += "Host: " + m_host + "\r\n\r\n";
        std::cout << "message:\n";
        std::cout << message.c_str() << '\n';
        m_socket.send_tcp(message.c_str());
    }

    void get2(std::string info_hash, unsigned short int port) {
        std::string message = "GET " + m_resource;
        message += "?info_hash=" + info_hash;
        message += "&peer_id=-qB4250-9gEX_cXQZ1wK";
        message += "&port=" + std::to_string(port);
        message += "&uploaded=0";
        message += "&downloaded=0";
        message += "&left=353159";
        message += "&corrupt=0";
        message += "&key=567ECB76";
        message += "&event=tarted";
        message += "&numwant=0";
        message += "&compact=1";
        message += "&no_peer_id=1";
        message += "&supportcrypto=1";
        message += "&redundant=0";
        message +=" HTTP/1.1\r\n";
        message += "Host: " + m_host + "\r\n\r\n";
        std::cout << "message:\n";
        std::cout << message.c_str() << '\n';
        m_socket.send_tcp(message.c_str());
    }
    void print() {
        std::cout << "Host: " << m_host << '\n';
        std::cout << "Resource: " << m_resource << '\n';
    }
};

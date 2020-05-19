#pragma once
#include <string>
#include <iostream>

class Requests {
private:
    std::string m_host;
    std::string m_resource;
public:
    Requests(std::string announce) {
        size_t pos = announce.rfind("/");
        if (pos != std::string::npos) {
            m_resource = announce.substr(pos, announce.size() - pos);
            m_host = announce.substr(0, pos);
        }
        else {
            throw std::invalid_argument("Accounce string incorrect format.");
        }
    }
    void get(std::string info_hash) {
        std::string message = "GET " + m_resource + " HTTP/1.1\r\n";
        message += "Host: " + m_host + "\r\n\r\n";
        std::cout << "message:\n";
        std::cout << message.c_str() << '\n';
    }
    void print() {
        std::cout << "Host: " << m_host << '\n';
        std::cout << "Resource: " << m_resource << '\n';
    }
};

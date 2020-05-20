/* test_request.cpp */
#include "../include/request.h"
#include "../include/socket.h"

int main() {
    std::string domain_name = "bt1.archive.org";
    unsigned short int port = 6969;
    std::string host = domain_name + ":6969";
    std::string resource = "/announce";
    std::string info_hash = "%ac%c3%b2%e43%d7%c7GZ%bbYA%b5h%1c%b7%a1%ea%26%e2";
    unsigned short int client_listening_port = 62921;
    Socket socket(domain_name, port);
    Request request(host, resource, socket);
    request.get2(info_hash, client_listening_port);
    return 0;
}

#include "../include/socket.h"

int main() {
    Socket socket("www.example.org", 80);
    socket.send_tcp("GET /index.php HTTP/1.1\r\nHost: www.example.org\r\n\r\n");
    return 0;
}

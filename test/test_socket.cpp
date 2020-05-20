#include "../include/socket.h"

int main() {
    /*
    Socket socket("www.example.org", 80);
    socket.send_tcp("GET /index.php HTTP/1.1\r\nHost: www.example.org\r\n\r\n");
    */
    Socket socket("bt1.archive.org", 6969);
    socket.send_tcp("GET /announce?info_hash=%ac%c3%b2%e43%d7%c7GZ%bbYA%b5h%1c%b7%a1%ea%26%e2&port=62921 HTTP/1.1\r\nHost: bt1.archive.org:6969\r\n\r\n");
    return 0;
}

#include <string>
#include <sstream>

#include "../hash.h"

int main() {
    std::string hash = "123456789abcdef123456789abcdef123456789a";
    std::string url_encoded;
    for (int i = 0; i < 40; i += 2) {
        std::stringstream ss;
        std::string s = hash.substr(i, 2);
        int x;
        ss << std::hex << s;
        ss >> x;
        unsigned char c = x;
        urlencoded += Hash::URL_Encode(&c, 1);
    }
    std::cout << url_encoded << std::endl;
    return 0;
}

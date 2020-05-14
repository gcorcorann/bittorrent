#include <string>
#include <iostream>
#include <vector>

#include "../read_binary.h"

int main() {
    std::string file("tests/test.torrent");
    std::cout << "Reading file... " << file << '\n';
    std::vector<unsigned char> buffer = readBinary(file);

    printBuffer(buffer);
    std::cout << std::endl;
    return 0;
}

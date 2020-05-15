#pragma once

#include <string>
#include <iostream>

#include <openssl/sha.h>


class Hash {
public:
    static unsigned char* Sha1(std::string encoded) {
        return SHA1((const unsigned char*) &encoded[0], encoded.size(), nullptr);
    }
    static void print(unsigned char* hash) {
        for (size_t i = 0; i < 20; ++i) {
            std::cout << std::hex << (int)hash[i];
        }
        std::cout << '\n';
    }
};

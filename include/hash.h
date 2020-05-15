#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

#include <openssl/sha.h>


class Hash {
public:
    static unsigned char* SHA1_Encode(std::string encoded) {
        return SHA1((const unsigned char*) &encoded[0], encoded.size(), nullptr);
    }
    static void print(unsigned char* hash) {
        for (size_t i = 0; i < 20; ++i) {
            std::cout << std::hex << (int)hash[i];
        }
        std::cout << '\n';
    }
    static std::string URL_Encode(unsigned char* hash) {
        std::ostringstream oss;
        oss.fill('0');
        oss << std::hex;
        for (size_t i = 0; i < 20; ++i) {
            if (std::isalnum(hash[i]) || hash[i] == '-' || hash[i] == '_' \
                    || hash[i] == '.' || hash[i] == '~') {
                oss << hash[i];
                continue;
            }
            // any other character is percent-encoded
            oss << '%' << std::setw(2) << int((unsigned char) hash[i]);
            oss << std::nouppercase;
        }
        return oss.str();
    }
};

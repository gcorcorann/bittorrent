#include <iostream>
#include <fstream>
#include <queue>
#include <string>

#include "binary.h"
#include "decoder.h"
#include "encoder.h"
#include "tokenize.h"
#include "value.h"
#include "hash.h"
#include "request.h"

struct Torrent {
    std::string url_encoded;
    std::string announce;
};

void GET_Request(Torrent torrent) {

    std::string request = "GET /announce?info_hash=" + torrent.url_encoded;
    request += " HTTP/1.1\r\n";
    request += "Host: " + torrent.announce.substr(0, torrent.announce.size() - 9) + "\r\n";
    std::cout << request << std::endl;
}

int main(int argc, const char* argv []) {
    if (argc < 2) {
        std::cout << "Error: usage ./a.out <torrent>\n";
        return 1;
    }
    std::string buffer = Binary::readString(argv[1]);
    std::cout << "Buffer:\n";
    std::cout << buffer << '\n' << '\n';

    std::queue<std::string> tokens;
    Tokenize::tokenize(buffer, tokens);

    Value decoded = Decoder::decode(tokens);
    std::cout << "Decoded:\n";
    Decoder::print(decoded);
    std::cout << '\n' << '\n';
    Value value = std::get<ValueMap>(decoded.data)["info"];

    std::string encoded = Encoder::encode(value);
    std::cout << "Encoded:\n";
    std::cout << encoded << '\n' << '\n';

    unsigned char* hash = Hash::SHA1_Encode(encoded);
    std::cout << "SHA1 Hash:\n";
    Hash::print(hash);
    std::cout << '\n';
    std::cout << "URL Encoded Hash:\n";
    std::string url_encoded = Hash::URL_Encode(hash);
    std::cout<< url_encoded << '\n' << '\n';

    // send url request
    Value announce_value = std::get<ValueMap>(decoded.data)["announce"];
    std::string announce = std::get<std::string>(announce_value.data);
    Request request(announce);  // set request with host url
    request.get(url_encoded);
    std::cout << std::endl;
    return 0;
}

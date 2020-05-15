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
    Value value = std::get<ValueMap>(decoded.data)["info"];
    std::cout << "Decoded:\n";
    Decoder::print(value);
    std::cout << '\n' << '\n';

    std::string encoded = Encoder::encode(value);
    std::cout << "Encoded:\n";
    std::cout << encoded << '\n' << '\n';

    unsigned char* hash = Hash::Sha1(encoded);
    std::cout << "SHA1 hash:\n";
    Hash::print(hash);
    std::cout << std::endl;
    return 0;
}

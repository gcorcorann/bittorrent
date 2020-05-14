#include <iostream>
#include <fstream>
#include <queue>
#include <string>

#include "read_binary.h"
#include "decoder.h"
#include "tokenize.h"
#include "value.h"


int main(int argc, const char* argv []) {
    if (argc < 2) {
        std::cout << "Error: usage ./a.out <torrent>\n";
        return 1;
    }
    std::vector<unsigned char> buffer = readBinary(argv[1]);
    printBuffer(buffer);
    /*
    std::queue<std::string> tokens;
    Tokenize::tokenize(line, tokens);
    Value decoded = Decoder::decode(tokens);
    Value value = std::get<ValueMap>(decoded.data)["info"];
    Decoder::print(value);

    // TODO: add encoder
    Encoder::encode(value);
    std::cout << std::endl;
    */
    return 0;
}

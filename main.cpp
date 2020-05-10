#include <fstream>
#include <regex>
#include <cassert>
#include <queue>
#include <string>
#include <sstream>

#include "decoder.h"
#include "tokenize.h"
#include "value.h"

int main(int argc, const char* argv []) {
    if (argc < 2) {
        std::cout << "Error: usage ./a.out <torrent>\n";
        return 1;
    }
    std::ifstream myfile(argv[1]);
    std::string line;
    if (myfile.is_open()) {
        std::getline(myfile, line);
        myfile.close();
    }
    else {
        std::cout << "Error: unable to open file.\n";
        return 1;
    }
    std::queue<std::string> tokens;
    Tokenize::tokenize(line, tokens);
    Value decoded = Decoder::decode(tokens);
    Decoder::print(decoded);
    return 0;
}

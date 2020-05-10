#include <string>
#include <queue>
#include <iostream>
#include <cassert>

#include "tokenize.h"
#include "decoder.h"
#include "value.h"

int main() {
    std::string sarray [] {"4:spam", "i-3e", "l4:spam4:eggse", "d3:cow3:moo4:spam4:eggse"};
    std::queue<std::string> tokens;
    for (size_t i = 0; i < sizeof(sarray) / sizeof(*sarray); ++i) {
        Tokenize::tokenize(sarray[i], tokens);
        Value decoded = Decoder::decode(tokens);
        Decoder::print(decoded);
        std::cout << std::endl;
    }
    return 0;
}

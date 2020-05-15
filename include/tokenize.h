#pragma once

#include <string>
#include <sstream>
#include <queue>
#include <regex>
#include <cassert>
#include <iostream>
#include <vector>
#include <iostream>
#include <regex>


class Tokenize {
public:
    static void tokenize(std::string encoded, std::queue<std::string>& out_tokens) {
        std::regex e ("([idle])|(\\d+):|(-?\\d+)");
        std::smatch sm;
        if (std::regex_search(encoded, sm, e)) {
            assert(sm.size() == 4);
            if (sm[2].str().empty()) {  // not string
                out_tokens.push(sm[0]);
                tokenize(encoded.substr(sm[0].str().size(),
                    encoded.size() - sm[0].str().size()), out_tokens);
            }
            else {
                std::istringstream iss;
                iss.str(sm[2]);
                unsigned int size = sm[0].str().size();
                unsigned int value;
                iss >> value;
                out_tokens.push("s");
                out_tokens.push(encoded.substr(size, value));
                tokenize(encoded.substr(size + value, encoded.size() - size + value),
                         out_tokens);
            }
        }
    }
};

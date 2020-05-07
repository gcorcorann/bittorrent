#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <cassert>
#include <queue>

using namespace std;

void tokenize(string encoded, queue<string>& tokens) {
    regex e ("([idle])|(\\d+):|(-?\\d+)");
    smatch sm;
    if (regex_search(encoded, sm, e)) {
        assert(sm.size() == 4);
        if (sm[2].str().empty()) {
            tokens.push(sm[0]);
            tokenize(encoded.substr(
                sm[0].str().size(), encoded.size() - sm[0].str().size()
                ), tokens);
        }
        else {
            std::istringstream stream(sm[2]);
            unsigned int size = sm[0].str().size();
            unsigned long long int value;
            stream >> value;
            tokens.push("s");
            tokens.push(encoded.substr(size, value));
            tokenize(encoded.substr(size + value, encoded.size() - size + value),
                     tokens);
        }
    }
}

void decodeInteger(queue<string>& tokens) {
    assert(tokens.front() == "i");
    if (tokens.size() < 3) {
        cout << "Error: integer tokens too short.\n";
        return;
    }
    tokens.pop();  // remove 'i'
    if (tokens.front() == "-0") {
        cout << "Error: invalid integer token.\n";
        return;
    }
    std::istringstream stream(tokens.front());
    long long int value;
    stream >> value;
    cout << value << '\n';
    tokens.pop();
    if (tokens.front() != "e") {
        cout << "Error: incorrect integer encoding.\n";
        return;
    }
}
void decodeList(queue<string>& tokens) {
    assert(tokens.front() == "l");
}
void decodeDict(queue<string>& tokens) {
    assert(tokens.front() == "d");
}
void decodeString(queue<string>& tokens) {
    assert(tokens.front() == "s");
}

void decode(queue<string>& tokens) {
    if (tokens.empty()) {
        cout << "Error: no tokens to decode.\n";
        return;
    }
    if (tokens.front() == "i") {
        decodeInteger(tokens);
        return;
    }
    if (tokens.front() == "l") {
        decodeList(tokens);
        return;
    }
    if (tokens.front() == "d") {
        decodeDict(tokens);
        return;
    }
    if (tokens.front() == "s") {
        decodeString(tokens);
        return;
    }
}
int main(int argc, const char* argv []) {
    if (argc < 2) {
        std::cout << "Error: usage ./a.out <torrent>\n";
        return 1;
    }
    ifstream myfile(argv[1]);
    string line;
    if (myfile.is_open()) {
        getline(myfile, line);
        myfile.close();
    }
    else {
        cout << "Error: unable to open file.\n";
        return 1;
    }
    queue<string> tokens;
    tokenize(line, tokens);
    while (!tokens.empty()) {
        cout << "[" << tokens.front() << "]";
        if (tokens.front() != "i") {
            tokens.pop();
        }
        decode(tokens);
    }
    return 0;
}

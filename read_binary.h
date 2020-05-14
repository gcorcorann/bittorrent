#pragma once

#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>

/*
 * Read binary file into unsigned char buffer, this function will return
 * an empty vector if no file is found.
 */
std::vector<unsigned char> readBinary(std::string file) {
    std::ifstream input(file, std::ios::binary);
    if (!input) {
        std::cout << "Error: could not read file " << file << '\n';
        return {};
    }
    // make input stream iterator from input stream
    // use vector constructor taking two iterators, beginning and end
    // end of stream iterator is equivalent to iterator created with default constructor
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    std::cout << "Successfully read " << buffer.size() << " bytes\n";
    return buffer;
}

void printBuffer(std::vector<unsigned char> buffer) {
    buffer.push_back('\0');
    std::cout << &buffer[0] << '\n';
    return;
}

#pragma once

#include <fstream>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>


class Binary {
public:
    /*
     * Read binary file into vector of unsigned chars, return an empty vector if
     * no file is found.
     */
    static std::vector<unsigned char> readVector(const char* filename) {
        std::ifstream input(filename, std::ios::in | std::ios::binary);
        if (!input) {
            std::cout << "Error: could not read file " << filename << '\n';
            return {};
        }
        // make input stream iterator from input stream
        // use vector constructor taking two iterators, beginning and end
        // end of stream iterator is equivalent to iterator created with default
        // constructor
        std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
        std::cout << "Successfully read " << buffer.size() << " bytes\n";
        input.close();
        return buffer;
    }
    
    /*
     * Read binary file into string, return an empty string if no file is found.
     */
    static std::string readString(const char* filename) {
        std::ifstream input(filename, std::ios::in | std::ios::binary);
        if (!input) {
            std::cout << "Error: could not read file " << filename << '\n';
            return "";
        }
        std::string buffer;
        input.seekg(0, std::ios::end);
        buffer.resize(input.tellg());  // return position of current character in input
        input.seekg(0, std::ios::beg);
        input.read(&buffer[0], buffer.size());
        input.close();
        return buffer;
    }
    
    static void printVector(std::vector<unsigned char>& buffer) {
        buffer.push_back('\0');
        std::cout << &buffer[0] << '\n';
        buffer.pop_back();
        return;
    }

    static void printString(std::string& buffer) {
        std::cout << buffer << '\n';
        return;
    }
};

#pragma once

#include <iostream>
#include <cassert>
#include <queue>
#include <string>
#include <sstream>

#include "value.h"

class Decoder {
public:
    static Value decode(std::queue<std::string>& tokens) {
        if (tokens.empty()) {
            throw std::invalid_argument("Error: no tokens to decode.");
        }
        if (tokens.front() == "i") {
            return decodeInteger(tokens);
        }
        if (tokens.front() == "s") {
            return decodeString(tokens);
        }
        if (tokens.front() == "l") {
            return decodeList(tokens);
        }
        if (tokens.front() == "d") {
            return decodeDict(tokens);
        }
        return {0};
    }
    static void print(Value decoded) {
        if (auto v = std::get_if<std::string>(&decoded.data)) {
            std::cout << *v;
            return;
        }
        if (auto v = std::get_if<int>(&decoded.data)) {
            std::cout << *v;
            return;
        }
        if (auto v = std::get_if<std::vector<Value>>(&decoded.data)) {
            printList(*v);
            return;
        }
        if (auto v = std::get_if<std::map<std::string, Value>>(&decoded.data)) {
            printDict(*v);
            return;
        }
    }
    static void printDict(std::map<std::string, Value>& dict) {
        std::cout << "{";
        int i = 1;
        for (auto it = dict.begin(); it != dict.end(); ++it, ++i) {
            std::cout << it->first << ": ";
            print(it->second);
            if (i != dict.size()) {  // don't print comma if end of dict
                std::cout << ", ";
            }
        }
        std::cout << "}";
    }
    static void printList(std::vector<Value>& vec) {
        std::cout << "[";
        int i = 1;
        for (auto it = vec.begin(); it != vec.end(); ++it, ++i) {
            print(*it);
            if (i != vec.size()) {  // don't print comma if end of list
                std::cout << ", ";
            }
        }
        std::cout << "]";
    }
private:
    static Value decodeInteger(std::queue<std::string>& tokens) {
        assert(tokens.front() == "i");
        if (tokens.size() < 3) {
            throw std::invalid_argument("Error: integer tokens too short.");
        }
        tokens.pop();  // remove "i"
        if (tokens.front() == "-0") {
            throw std::invalid_argument("Error: invalid integer token.");
        }
        std::istringstream iss(tokens.front());
        int i;
        iss >> i;
        tokens.pop();  // remove integer value
        if (tokens.front() != "e") {
            throw std::invalid_argument("Error: incorrect integer encoding.");
        }
        tokens.pop();  // remove "e"
        return {i};
    }
    static Value decodeString(std::queue<std::string>& tokens) {
        assert(tokens.front() == "s");
        tokens.pop();  // remove "s"
        std::string s = tokens.front();
        tokens.pop();  // remove string value
        return {s};
    }
    static Value decodeList(std::queue<std::string>& tokens) {
        assert(tokens.front() == "l" || tokens.front() == "d");
        tokens.pop();  // remove "l" or "d"
        std::vector<Value> vec;
        while (tokens.front() != "e") {
            vec.push_back(decode(tokens));
        }
        tokens.pop();  // remove "e"
        return {vec};
    }
    static Value decodeDict(std::queue<std::string>& tokens) {
        assert(tokens.front() == "d");
        std::vector<Value> vec = std::get<std::vector<Value>>(decodeList(tokens).data);
        std::map<std::string, Value> dict;
        for (size_t i = 0; i < vec.size(); i += 2) {
            dict[std::get<std::string>(vec[i].data)] = vec[i+1];
        }
        return {dict};
    }
};

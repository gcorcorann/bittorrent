#pragma once

#include <string>
#include <iostream>

#include "value.h"


class Encoder {
public:
    static std::string encode(const Value& decoded) {
        if (auto v = std::get_if<std::string>(&decoded.data)) {
            return encodeString(*v);
        }
        if (auto v = std::get_if<int>(&decoded.data)) {
            return encodeInteger(*v);
        }
        if (auto v = std::get_if<ValueVector>(&decoded.data)) {
            return encodeList(*v);
        }
        if (auto v = std::get_if<ValueMap>(&decoded.data)) {
            return encodeDict(*v);
        }
        throw std::invalid_argument("Error: cannot encode input.");
        return "";
    }

private:
    static std::string encodeString(std::string string_data) {
        unsigned int string_len = string_data.size();
        return std::to_string(string_len) + ":" + string_data;
    }
    static std::string encodeInteger(int integer_data) {
        std::string bencode = "i";
        bencode += std::to_string(integer_data) + "e";
        return bencode;
    }
    static std::string encodeList(ValueVector list_data) {
        std::string bencode = "l";
        for (auto it = list_data.begin(); it != list_data.end(); ++it) {
            bencode += encode(*it);
        }
        bencode += "e";
        return bencode;
    }
    static std::string encodeDict(ValueMap dict_data) {
        std::string bencode = "d";
        for (auto it = dict_data.begin(); it != dict_data.end(); ++it) {
            bencode += encodeString(it->first) + encode(it->second);
        }
        bencode += "e";
        return bencode;
    }
};

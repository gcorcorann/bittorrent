#pragma once
#include <string>
#include <vector>
#include <map>
#include <variant>

struct Value {
    std::variant<int, std::string, std::vector<Value>, std::map<std::string, Value>> data;
};

using ValueVector = std::vector<Value>;
using ValueMap = std::map<std::string, Value>;

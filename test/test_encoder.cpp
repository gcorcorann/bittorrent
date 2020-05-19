#include <map>
#include <string>
#include <iostream>

#include "../value.h"
#include "../encoder.h"


int main() {
    ValueMap vm = {{"cow", {"moo"}},
                   {"spam", {"eggs"}}};
    ValueVector vv = {{"spam"}, {"eggs"}};

    Value value_string = {"spam"};
    Value value_integer = {-3};
    Value value_dict = {vm};
    Value value_list = {vv};

    std::string encoded = Encoder::encode(value_string);
    std::cout << encoded << std::endl;
    encoded = Encoder::encode(value_integer);
    std::cout << encoded << std::endl;
    encoded = Encoder::encode(value_list);
    std::cout << encoded << std::endl;
    encoded = Encoder::encode(value_dict);
    std::cout << encoded << std::endl;
    return 0;
}

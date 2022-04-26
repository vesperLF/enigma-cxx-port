#pragma once

#include <set>
#include <string>

class plugboard {
private:
    int* wiring;
public:
    plugboard(const std::string&);
    ~plugboard();
    int forward(int);
    static std::set<int> get_unplugged_characters(const std::string&);
};

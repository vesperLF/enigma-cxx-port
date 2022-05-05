#pragma once

#include <set>
#include <string>
#include <vector>

class enigma_key_t {
public:
    std::vector<int> rotors = {1, 2, 3};
    int indicators[3] = {0, 0, 0};
    int rings[3] = {0, 0, 0};
    std::set<std::pair<char, char>> plugboard;
    std::string plugboard_str();
};

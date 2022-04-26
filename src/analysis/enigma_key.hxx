#pragma once

#include <set>
#include <vector>

class enigma_key {
public:
    std::vector<int> rotors = {1, 2, 3};
    int indicators[3] = {0, 0, 0};
    int rings[3] = {0, 0, 0};
    std::set<std::pair<char, char>> plugboard;
};

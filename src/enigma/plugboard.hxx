#pragma once

#include <set>
#include <vector>

class plugboard {
private:
    std::vector<int> wiring;
public:
    plugboard(const std::set<std::pair<char, char>>& = {});
    int forward(int);
    static std::set<int> get_unplugged_characters(const std::set<std::pair<char, char>>&);
};

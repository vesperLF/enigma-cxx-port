#pragma once

#include <set>
#include <vector>

class plugboard_t {
private:
    std::vector<int> wiring;
public:
    plugboard_t(const std::set<std::pair<char, char>>& = {});
    int forward(int);
    static std::set<int> get_unplugged_characters(const std::set<std::pair<char, char>>&);
};

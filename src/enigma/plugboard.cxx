#include "plugboard.hxx"

plugboard_t::plugboard_t(const std::set<std::pair<char, char>>& connections) {
    wiring.resize(26);
    for (int i = 0; i < 26; i++) {
        wiring[i] = i;
    }
    for (const std::pair<char, char>& connection : connections) {
        wiring[connection.first - 65] = connection.second - 65;
        wiring[connection.second - 65] = connection.first - 65;
    }
}

int plugboard_t::forward(int c) {
    return wiring[c];
}

std::set<int> plugboard_t::get_unplugged_characters(const std::set<std::pair<char, char>>& connections) {
    std::set<int> unplugged_characters = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
    for (const std::pair<char, char>& connection : connections) {
        unplugged_characters.erase(unplugged_characters.find(connection.first - 65));
        unplugged_characters.erase(unplugged_characters.find(connection.second - 65));
    }
    return unplugged_characters;
}

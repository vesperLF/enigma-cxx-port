#include "plugboard.hxx"

plugboard::plugboard(const std::string& connections) {
    wiring = new int[26];
    for (int i = 0; i < 26; i++) {
        wiring[i] = i;
    }
    char c1 = 0, c2 = 0;
    for (char c : connections) {
        if (c >= 'A' && c <= 'Z') {
            if (c1 == 0) {
                c1 = c;
            } else if (c2 == 0) {
                c2 = c;
                wiring[c1 - 65] = c2 - 65;
                wiring[c2 - 65] = c1 - 65;
            } else {
                throw 3;
            }
        } else {
            c1 = 0;
            c2 = 0;
        }
    }
}

plugboard::~plugboard() {
    delete[] wiring;
}

int plugboard::forward(int c) {
    return wiring[c];
}

std::set<int> plugboard::get_unplugged_characters(const std::string& connections) {
    std::set<int> unplugged_characters = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25 };
    for (char c : connections) {
        if (c >= 'A' && c <= 'Z') {
            unplugged_characters.erase(unplugged_characters.find(c - 65));
        }
    }
    return unplugged_characters;
}

#include "enigma_key.hxx"

std::string enigma_key_t::plugboard_str() {
    std::string result;
    for (std::pair<char, char> plug: plugboard) {
        result += plug.first;
        result += plug.second;
        result += ' ';
    }
    result.pop_back();
    return result;
}

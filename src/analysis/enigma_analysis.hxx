#pragma once

#include "scored_enigma_key.hxx"
#include "..\enigma\enigma.hxx"

namespace enigma_analysis {
    enum class available_rotors {
        THREE = 3,
        FIVE = 5,
        EIGHT = 8
    };

    std::vector<scored_enigma_key_t> find_rotor_configuration(const std::string& cipher_text, available_rotors, const std::set<std::pair<char, char>>&, int, float(*)(const char*));
    scored_enigma_key_t find_ring_settings(const std::string&, const enigma_key_t&, float(*)(const char*));
}

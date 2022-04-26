#pragma once

#include "scored_enigma_key.hxx"
#include "..\enigma\enigma.hxx"

namespace enigma_analysis {
    enum class available_rotors {
        THREE = 3,
        FIVE = 5,
        EIGHT = 8
    };

    std::vector<scored_enigma_key> find_rotor_configuration(const std::string& cipher_text, available_rotors, const std::set<std::pair<char, char>>&, int, float(*fitness_function)(const char*));
}

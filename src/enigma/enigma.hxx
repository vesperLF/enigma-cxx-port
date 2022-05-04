#pragma once

#include "rotor.hxx"
#include "reflector.hxx"
#include "plugboard.hxx"
#include "..\analysis\enigma_key.hxx"

class enigma_t {
public:
    rotor_t left_rotor, middle_rotor, right_rotor;
    reflector_t reflector;
    plugboard_t plugboard;
    enigma_t(rotor_t l, rotor_t m, rotor_t r, reflector_t r2, plugboard_t pb) : left_rotor(l), middle_rotor(m), right_rotor(r), reflector(r2), plugboard(pb) {}
    enigma_t(const enigma_key_t&);
    void rotate();
    std::string encrypt(const std::string&);
};

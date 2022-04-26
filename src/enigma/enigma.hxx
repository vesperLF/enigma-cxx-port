#pragma once

#include "rotor.hxx"
#include "reflector.hxx"
#include "plugboard.hxx"
#include "..\analysis\enigma_key.hxx"

class enigma {
public:
    rotor left_rotor, middle_rotor, right_rotor;
    reflector reflect;
    plugboard plugs;
    enigma(rotor l, rotor m, rotor r, reflector r2, plugboard pb) : left_rotor(l), middle_rotor(m), right_rotor(r), reflect(r2), plugs(pb) {}
    enigma(const enigma_key&);
    void rotate();
    std::string encrypt(const std::string&);
};

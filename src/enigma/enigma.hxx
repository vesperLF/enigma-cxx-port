#pragma once

#include "rotor.hxx"
#include "reflector.hxx"
#include "plugboard.hxx"

class enigma {
public:
    rotor left_rotor, middle_rotor, right_rotor;
    reflector reflect;
    plugboard plugs;
    void rotate();
    std::string encrypt(const std::string&);
};

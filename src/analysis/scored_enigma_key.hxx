#pragma once

#include "enigma_key.hxx"

class scored_enigma_key : public enigma_key {
public:
    float score;
    scored_enigma_key(const enigma_key& = {}, float = -1e30f);
};

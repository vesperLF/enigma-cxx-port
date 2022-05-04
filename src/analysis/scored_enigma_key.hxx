#pragma once

#include "enigma_key.hxx"

class scored_enigma_key_t : public enigma_key_t {
public:
    float score;
    scored_enigma_key_t(const enigma_key_t& = {}, float = -1e30f);
};

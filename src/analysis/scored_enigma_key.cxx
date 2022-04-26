#include "scored_enigma_key.hxx"

scored_enigma_key::scored_enigma_key(const enigma_key& key, float new_score) {
    rotors = key.rotors;
    indicators[0] = key.indicators[0];
    indicators[1] = key.indicators[1];
    indicators[2] = key.indicators[2];
    rings[0] = key.rings[0];
    rings[1] = key.rings[1];
    rings[2] = key.rings[2];
    plugboard = key.plugboard;
    score = new_score;
}

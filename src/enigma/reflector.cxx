#include "reflector.hxx"
#include "decode.hxx"

const char a_encoding[27] = "ZYXWVUTSRQPONMLKJIHGFEDCBA";
const char b_encoding[27] = "YRUHQSLDPXNGOKMIEBFZCWVJAT";
const char c_encoding[27] = "FVPJIAOYEDRZXWGCTKUQSBNMHL";

const std::array<int, 26> a_wiring = decode(a_encoding);
const std::array<int, 26> b_wiring = decode(b_encoding);
const std::array<int, 26> c_wiring = decode(c_encoding);


reflector_t::reflector_t(char c) {
    switch (c) {
    case 'B':
        wiring = b_wiring.data();
        break;
    case 'C':
        wiring = c_wiring.data();
        break;
    default:
        wiring = a_wiring.data();
    }
}

int reflector_t::forward(int c) {
    return wiring[c];
}

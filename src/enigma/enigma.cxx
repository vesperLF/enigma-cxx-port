#include "enigma.hxx"

enigma_t::enigma_t(const enigma_key_t& key) {
    left_rotor = rotor_t(key.rotors[0], key.indicators[0], key.rings[0]);
    middle_rotor = rotor_t(key.rotors[1], key.indicators[1], key.rings[1]);
    right_rotor = rotor_t(key.rotors[2], key.indicators[2], key.rings[2]);
    plugboard = key.plugboard;
}

void enigma_t::rotate() {
    if (middle_rotor.is_at_notch()) {
        middle_rotor.turnover();
        left_rotor.turnover();
    } else if (right_rotor.is_at_notch()) {
        middle_rotor.turnover();
    }
    right_rotor.turnover();
}

std::string enigma_t::encrypt(const std::string& input) {
    std::string output(input.length(), ' ');
    for (int i = 0; i < input.length(); i++) {
        char c = input[i] - 65;
        rotate();
        output[i] =  plugboard.forward(
            right_rotor.backward(
                middle_rotor.backward(
                    left_rotor.backward(
                        reflector.forward(
                            left_rotor.forward(
                                middle_rotor.forward(
                                    right_rotor.forward(
                                        plugboard.forward(c)
                                    )
                                )
                            )
                        )
                    )
                )
            )
        ) + 65;
    }
    return output;
}

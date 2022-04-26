#include "enigma.hxx"

void enigma::rotate() {
    if (middle_rotor.is_at_notch()) {
        middle_rotor.turnover();
        left_rotor.turnover();
    } else if (right_rotor.is_at_notch()) {
        middle_rotor.turnover();
    }
    right_rotor.turnover();
}

std::string enigma::encrypt(const std::string& input) {
    std::string output(input.length(), ' ');
    for (int i = 0; i < input.length(); i++) {
        rotate();
        output[i] =  plugs.forward(
            right_rotor.backward(
                middle_rotor.backward(
                    left_rotor.backward(
                        reflect.forward(
                            left_rotor.forward(
                                middle_rotor.forward(
                                    right_rotor.forward(
                                        plugs.forward(input[i] - 65)
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

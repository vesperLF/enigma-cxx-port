#include "rotor.hxx"
#include "decode.hxx"

const char encodings[8][27] {
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
    "AJDKSIRUXBLHWTMCQGZNPYFVOE",
    "BDFHJLCPRTXVZNYEIWGAKMUSQO",
    "ESOVPZJAYQUIRHXLNFTGKDCMWB",
    "VZBRGITYUPSDNHLXAWMJQOFECK",
    "JPGVOUMFYQBENHZRDKASXLICTW",
    "NZJHGRCXMYSWBOUFAIVLPEKQDT",
    "FKQHTLXOCBJSPDZRAMEWNIUYGV"
};

constexpr std::array<std::array<int, 26>, 8> decode_eightfold(const char** pp) {
    std::array<std::array<int, 26>, 8> result {};
    for (int i = 0; i < 8; i++) {
        result[i] = decode(pp[i]);
    }
    return result;
}

const std::array<std::array<int, 26>, 8> wirings = decode_eightfold((const char**)encodings);

rotor::rotor(int name, int rotor_pos, int ring_setting) {
    name_code = name - 1;
    rotor_position = rotor_pos;
    ring_position = ring_setting;
    static const int notch_positions[8] {
        16,
        4,
        21,
        9,
        25,
        12,
        12,
        12
    };
    notch_position_1 = notch_positions[name];
    notch_position_2 = name < 5 ? -1 : 25;
    wiring = wirings[name].data();
}

const std::string& rotor::get_name() {
    static const std::string names[8] {
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII",
        "VIII"
    };
    return names[name_code];
}

int rotor::forward(int c) {
    int shift = rotor_position - ring_position;
    return (wiring[(c + shift + 26) % 26] - shift + 26) % 26;
}

int rotor::backward(int c) {
    int shift = rotor_position - ring_position;
    return (wiring[26 - ((c + shift + 26) % 26)] - shift + 26) % 26;
}

bool rotor::is_at_notch() {
    return rotor_position == notch_position_1 || rotor_position == notch_position_2;
}

void rotor::turnover() {
    rotor_position = (rotor_position + 1) % 26;
}

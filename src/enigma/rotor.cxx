#include "rotor.hxx"
#include "decode.hxx"



constexpr std::array<std::array<int, 26>, 8> decode_eightfold() {
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
    std::array<std::array<int, 26>, 8> result {};
    for (int i = 0; i < 8; i++) {
        result[i] = decode(encodings[i]);
    }
    return result;
}

constexpr std::array<std::array<int, 26>, 8> invert(const std::array<std::array<int, 26>, 8>& forward_wiring) {
    std::array<std::array<int, 26>, 8> result {};
    for (int i = 0; i < 8; i++) {
        for (int ii = 0; ii < 26; ii++) {
            result[i][forward_wiring[i][ii]] = ii;
        }
    }
    return result;
}

const std::array<std::array<int, 26>, 8> rotor_t::wirings = decode_eightfold();
const std::array<std::array<int, 26>, 8> rotor_t::inverse_wirings = invert(wirings);

const std::array<std::string, 8> names {
        "I",
        "II",
        "III",
        "IV",
        "V",
        "VI",
        "VII",
        "VIII"
};

const int notch_positions[8] {
        16,
        4,
        21,
        9,
        25,
        12,
        12,
        12
};

void rotor_t::constructor_helper(int name, int rotor_pos, int ring_setting) {
    name_code = name - 1;
    rotor_position = rotor_pos;
    ring_position = ring_setting;
    notch_position_1 = notch_positions[name_code];
    notch_position_2 = name_code < 5 ? -1 : 25;
    wiring = wirings[name_code].data();
    inverse = inverse_wirings[name_code].data();
}

rotor_t::rotor_t(int name, int rotor_pos, int ring_setting) {
    constructor_helper(name, rotor_pos, ring_setting);
}

rotor_t::rotor_t(const std::string& name, int rotor_pos, int ring_setting) {
    name_code = -9;
    for (int i = 0; i < 8; i++) {
        if (name == names[i]) {
            name_code = i;
            break;
        }
    }
    if (name_code == -9) {
        throw name_code;
    }
    constructor_helper(name_code + 1, rotor_pos, ring_setting);
}

const std::string& rotor_t::get_name() {
    return names[name_code];
}

int rotor_t::forward(int c) {
    int shift = rotor_position - ring_position;
    return (wiring[(c + shift + 26) % 26] - shift + 26) % 26;
}

int rotor_t::backward(int c) {
    int shift = rotor_position - ring_position;
    return (inverse[(c + shift + 26) % 26] - shift + 26) % 26;
}

bool rotor_t::is_at_notch() {
    return rotor_position == notch_position_1 || rotor_position == notch_position_2;
}

void rotor_t::turnover() {
    rotor_position = (rotor_position + 1) % 26;
}

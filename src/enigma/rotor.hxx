#pragma once

#include <string>

class rotor_t {
private:
    int name_code;
    const int* wiring;
    const int* inverse;
    int rotor_position;
    int notch_position_1;
    int notch_position_2;
    int ring_position;
    static const std::array<std::array<int, 26>, 8> wirings;
    static const std::array<std::array<int, 26>, 8> inverse_wirings;
    void constructor_helper(int, int, int);
public:
    rotor_t(int name = 1, int rotor_pos = 0, int ring_setting = 0);
    rotor_t(const std::string&, int rotor_pos = 0, int ring_setting = 0);
    const std::string& get_name();
    int forward(int);
    int backward(int);
    bool is_at_notch();
    void turnover();
};

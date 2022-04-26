#pragma once

#include <string>

class rotor {
private:
    int name_code;
    const int* wiring;
    int rotor_position;
    int notch_position_1;
    int notch_position_2;
    int ring_position;
public:
    rotor(int name = 1, int rotor_pos = 0, int ring_setting = 0);
    const std::string& get_name();
    int forward(int);
    int backward(int);
    bool is_at_notch();
    void turnover();
};

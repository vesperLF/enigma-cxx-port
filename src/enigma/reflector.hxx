#pragma once

class reflector_t {
private:
    const int* wiring;
public:
    reflector_t(char = 'B');
    int forward(int);
};

#pragma once

class reflector {
private:
    const int* wiring;
public:
    reflector(char = 'B');
    int forward(int);
};

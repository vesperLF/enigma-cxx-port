#pragma once

class reflector {
private:
    const int* wiring;
public:
    reflector(char);
    int forward(int);
};

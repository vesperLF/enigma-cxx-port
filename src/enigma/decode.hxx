#pragma once
#include <array>

constexpr std::array<int, 26> decode(const char* p) {
    std::array<int, 26> result;
    for (int i = 0; i < 26; i++) {
        result[i] = p[i] - 65;
    }
    return result;
}

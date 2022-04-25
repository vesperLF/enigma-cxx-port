#include "frequency_analysis.hxx"

void frequency_analysis::analyze(char* text) {
    for (; *text != 0; text++) {
        counts[*text - 65]++;
        total++;
    }
}

float* frequency_analysis::frequencies() {
    float* freq = new float[26];
    for (int i = 0; i < 26; i++) {
        freq[i] = counts[i] / total;
    }
    return freq;
}

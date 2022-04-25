#pragma once

class frequency_analysis {
private:
    float counts[26];
    int total;
public:
    void analyze(char*);

    //output is heap-allocated via new[], remember to delete[] it when you're done
    float* frequencies();
};

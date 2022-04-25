#include "fitness_functions.hxx"
#include "n_grams_data.hxx"

float single_character_fitness(char* text) {
    float fitness = 0;
    for (; *text != 0; text++) {
        fitness += singles[*text - 65];
    }
    return fitness;
}

float bigram_fitness(char* text) {
    float fitness = 0;
    int current;
    int next = text[0] - 65;
    for (int i = 1; text[i] != 0; i++) {
        current = next;
        next = text[i] - 65;
        fitness += bigrams[(current << 5) | next];
    }
    return fitness;
}

float trigram_fitness(char* text) {
    float fitness = 0;
    int current;
    int next1 = text[0] - 65;
    int next2 = text[1] - 65;
    for (int i = 2; text[i] != 0; i++) {
        current = next1;
        next1 = next2;
        next2 = text[i] - 65;
        fitness += trigrams[(current << 10) | (next1 << 5) | next2];
    }
    return fitness;
}

float quadgram_fitness(char* text) {
    float fitness = 0;
    int current;
    int next1 = text[0] - 65;
    int next2 = text[1] - 65;
    int next3 = text[2] - 65;
    for (int i = 3; text[i] != 0; i++) {
        current = next1;
        next1 = next2;
        next2 = next3;
        next3 = text[i] - 65;
        fitness += quadgrams[(current << 15) | (next1 << 10) | (next2 << 5) | next3];
    }
    return fitness;
}

float ioc_fitness(char* text) {
    int histogram[26];
    int length = 1;
    for (char* p = text; *p != 0; p++) {
        histogram[*p - 65]++;
        length++;
    }
    float total = 0.0f;
    for (int v : histogram) {
        total += v * (v - 1);
    }
    return total / (length * (length - 1));
}

float known_plaintext_fitness(char* text, char* known_text) {
    int total = 0;
    for (int i = 0; text[i] != 0 && known_text[i] != 0; i++) {
        if (known_text[i] == text[i]) {
            total++;
        }
    }
    return total;
}

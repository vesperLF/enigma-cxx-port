#pragma once
#include <string>
#include <vector>
#include <utility>

float single_character_fitness(const char*);
float bigram_fitness(const char*);
float trigram_fitness(const char*);
float quadgram_fitness(const char*);
float ioc_fitness(const char*);

//Note: known_text is null-terminated, unlike Mike's Java implementation which can contain null throughout.
float known_plaintext_fitness(const char* text, const char* known_text);
std::string get_known_text_string(const std::vector<std::pair<std::string, size_t>>&);
inline float known_plaintext_fitness(const char* text, const std::vector<std::pair<std::string, size_t>>& word_offset_pairs) {
    return known_plaintext_fitness(text, get_known_text_string(word_offset_pairs).c_str());
}

#pragma once

float single_character_fitness(const char*);
float bigram_fitness(const char*);
float trigram_fitness(const char*);
float quadgram_fitness(const char*);
float ioc_fitness(const char*);

//Note: known_text is null-terminated, unlike Mike's Java implementation which can contain null throughout.
float known_plaintext_fitness(const char* text, const char* known_text);

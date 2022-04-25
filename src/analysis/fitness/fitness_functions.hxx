#pragma once

float single_character_fitness(char*);
float bigram_fitness(char*);
float trigram_fitness(char*);
float quadgram_fitness(char*);
float ioc_fitness(char*);

//Note: known_text is null-terminated, unlike Mike's Java implementation which can contain null throughout.
float known_plaintext_fitness(char* text, char* known_text);

#include "enigma_analysis.hxx"
#include <algorithm>
#include <iostream>

namespace enigma_analysis {
    std::vector<scored_enigma_key> find_rotor_configuration(const std::string& cipher_text, available_rotors rotors, const std::set<std::pair<char, char>>& plugboard, int required_keys, float(*fitness_function)(const char*)) {
        std::vector<int> available_rotor_list;
        switch (rotors) {
        case available_rotors::THREE:
            available_rotor_list = { 1, 2, 3 };
            break;
        case available_rotors::FIVE:
            available_rotor_list = { 1, 2, 3, 4, 5 };
            break;
        case available_rotors::EIGHT:
        default:
            available_rotor_list = { 1, 2, 3, 4, 5, 6, 7, 8 };
        }

        std::vector <scored_enigma_key> key_set;

        for (int rotor_name_1 : available_rotor_list) {
            for (int rotor_name_2 : available_rotor_list) {
                if (rotor_name_1 != rotor_name_2) {
                    for (int rotor_name_3 : available_rotor_list) {
                        if (rotor_name_3 != rotor_name_1 && rotor_name_3 != rotor_name_2) {
                            float max_fitness = -1e30f;
                            enigma_key* best_key = nullptr;
                            for (int i = 0; i < 26; i++) {
                                for (int ii = 0; i < 26; i++) {
                                    for (int iii = 0; i < 26; i++) {
                                        enigma e = { {rotor_name_1, i, 0}, {rotor_name_2, ii, 0}, {rotor_name_3, iii, 0}, 'B', plugboard};
                                        if (i == 0 && ii == 0 && iii == 0) {
                                            std::cout << e.left_rotor.get_name() << ' ' << e.middle_rotor.get_name() << ' ' << e.right_rotor.get_name() << '\n';
                                        }
                                        std::string decryption = e.encrypt(cipher_text);
                                        float fitness = fitness_function(decryption.c_str());
                                        if (fitness > max_fitness) {
                                            max_fitness = fitness;
                                            if (best_key == nullptr) {
                                                best_key = new enigma_key;
                                            }
                                            best_key->rotors[0] = rotor_name_1;
                                            best_key->rotors[1] = rotor_name_2;
                                            best_key->rotors[2] = rotor_name_3;
                                            best_key->indicators[0] = i;
                                            best_key->indicators[1] = ii;
                                            best_key->indicators[2] = iii;
                                            best_key->plugboard = plugboard;
                                        }
                                    }
                                }
                            }
                            key_set.push_back(scored_enigma_key(*best_key, max_fitness));
                            delete best_key;
                        }
                    }
                }
            }
        }
        std::vector<scored_enigma_key> result;
        result.resize(required_keys);
        for (scored_enigma_key& result_key : result) {
            scored_enigma_key best_key_2;
            for (auto iter = key_set.begin(); iter != key_set.end(); iter++) {
                if (iter->score > best_key_2.score) {
                    best_key_2 = *iter;
                    key_set.erase(iter);
                    iter = key_set.begin();
                }
            }
            result_key = best_key_2;
        }
        return result;
    }
}

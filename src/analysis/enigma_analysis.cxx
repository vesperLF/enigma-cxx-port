#include "enigma_analysis.hxx"
#include <algorithm>
#include <iostream>

namespace enigma_analysis {
    std::vector<scored_enigma_key_t> find_rotor_configuration(const std::string& cipher_text, available_rotors rotors, const std::set<std::pair<char, char>>& plugboard, int required_keys, float(*fitness_function)(const char*)) {
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

        std::vector <scored_enigma_key_t> key_set;

        for (int rotor_name_1 : available_rotor_list) {
            for (int rotor_name_2 : available_rotor_list) {
                if (rotor_name_1 != rotor_name_2) {
                    for (int rotor_name_3 : available_rotor_list) {
                        if (rotor_name_3 != rotor_name_1 && rotor_name_3 != rotor_name_2) {
                            float max_fitness = -1e30f;
                            enigma_key_t* best_key = nullptr;
                            for (int i = 0; i < 26; i++) {
                                for (int ii = 0; ii < 26; ii++) {
                                    for (int iii = 0; iii < 26; iii++) {
                                        enigma_t e = { {rotor_name_1, i, 0}, {rotor_name_2, ii, 0}, {rotor_name_3, iii, 0}, 'B', plugboard};
                                        if (i == 0 && ii == 0 && iii == 0) {
                                            std::cout << e.left_rotor.get_name() << ' ' << e.middle_rotor.get_name() << ' ' << e.right_rotor.get_name() << '\n';
                                        }
                                        float fitness = fitness_function(e.encrypt(cipher_text).c_str());
                                        if (fitness > max_fitness) {
                                            max_fitness = fitness;
                                            if (best_key == nullptr) {
                                                best_key = new enigma_key_t;
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
                            key_set.push_back(scored_enigma_key_t(*best_key, max_fitness));
                            delete best_key;
                        }
                    }
                }
            }
        }
        std::vector<scored_enigma_key_t> result;
        result.resize(required_keys);
        for (scored_enigma_key_t& result_key : result) {
            std::vector<scored_enigma_key_t>::iterator best_iter;
            for (std::vector<scored_enigma_key_t>::iterator iter = key_set.begin(); iter != key_set.end(); iter++) {
                if (iter->score > result_key.score) {
                    result_key = *iter;
                    best_iter = iter;
                    iter = key_set.begin();
                }
            }
            key_set.erase(best_iter);
        }
        return result;
    }

    template<int ROTOR_INDEX> int find_ring_setting(enigma_key_t key, const std::string& cipher_text, float(*fitness_function)(const char*)) {
        float max_fitness = -1e30f;
        int optimal_ring_setting = 0;
        const int original_indicator = key.indicators[ROTOR_INDEX];
        
        for (int i = 0; i < 26; i++) {
            key.indicators[ROTOR_INDEX] = (original_indicator + i) % 26;
            key.rings[ROTOR_INDEX] = i;
            float fitness = fitness_function(enigma_t(key).encrypt(cipher_text).c_str());
            if (fitness > max_fitness) {
                max_fitness = fitness;
                optimal_ring_setting = i;
            }
        }
        return optimal_ring_setting;
    }

    template<int ROTOR_INDEX> void optimize_ring_setting(enigma_key_t& key, const std::string& cipher_text, float(*fitness_function)(const char*)) {
        int optimal_index = find_ring_setting<ROTOR_INDEX>(key, cipher_text, fitness_function);
        key.rings[ROTOR_INDEX] = optimal_index;
        key.indicators[ROTOR_INDEX] = (key.indicators[ROTOR_INDEX] + optimal_index) % 26;
    }
    
    scored_enigma_key_t find_ring_settings(const std::string& cipher_text, const enigma_key_t& key, float(*fitness_function)(const char*)) {
        scored_enigma_key_t result(key);
        const int right_rotor_index = 2, middle_rotor_index = 1;
        optimize_ring_setting<right_rotor_index>(result, cipher_text, fitness_function);
        optimize_ring_setting<middle_rotor_index>(result, cipher_text, fitness_function);
        result.score = fitness_function(enigma_t(result).encrypt(cipher_text).c_str());
        return result;
    }
}

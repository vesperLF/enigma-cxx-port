#include "analysis\enigma_analysis.hxx"
#include "analysis\fitness\fitness_functions.hxx"
#include <chrono>
#include <iostream>

int main() {
    const std::chrono::time_point start_time = std::chrono::system_clock::now();

    // For those interested, these were the original settings
    // II V III / 7 4 19 / 12 2 20 / AF TV KO BL RW
    std::string cipher_text = "OZLUDYAKMGMXVFVARPMJIKVWPMBVWMOIDHYPLAYUWGBZFAFAFUQFZQISLEZMYPVBRDDLAGIHIFUJDFADORQOOMIZPYXDCBPWDSSNUSYZTJEWZPWFBWBMIEQXRFASZLOPPZRJKJSPPSTXKPUWYSKNMZZLHJDXJMMMDFODIHUBVCXMNICNYQBNQODFQLOGPZYXRJMTLMRKQAUQJPADHDZPFIKTQBFXAYMVSZPKXIQLOQCVRPKOBZSXIUBAAJBRSNAFDMLLBVSYXISFXQZKQJRIQHOSHVYJXIFUZRMXWJVWHCCYHCXYGRKMKBPWRDBXXRGABQBZRJDVHFPJZUSEBHWAEOGEUQFZEEBDCWNDHIAQDMHKPRVYHQGRDYQIOEOLUBGBSNXWPZCHLDZQBWBEWOCQDBAFGUVHNGCIKXEIZGIZHPJFCTMNNNAUXEVWTWACHOLOLSLTMDRZJZEVKKSSGUUTHVXXODSKTFGRUEIIXVWQYUIPIDBFPGLBYXZTCOQBCAHJYNSGDYLREYBRAKXGKQKWJEKWGAPTHGOMXJDSQKYHMFGOLXBSKVLGNZOAXGVTGXUIVFTGKPJU";
    
    std::vector<scored_enigma_key_t> rotor_configurations = enigma_analysis::find_rotor_configuration(cipher_text, enigma_analysis::available_rotors::FIVE, {}, 10, ioc_fitness);

    std::cout << "\nTop 10 rotor configurations:\n";
    for (scored_enigma_key_t& sek : rotor_configurations) {
        std::cout << rotor_t(sek.rotors[0]).get_name() << ' ' << rotor_t(sek.rotors[1]).get_name() << ' ' << rotor_t(sek.rotors[2]).get_name() << " / " << sek.indicators[0] << ' ' << sek.indicators[1] << ' ' << sek.indicators[2] << " / " << sek.score << '\n';
    }
    std::cout << "Current decryption: " << enigma_t(rotor_configurations[0]).encrypt(cipher_text) << '\n';

    scored_enigma_key_t rotor_and_ring_configuration = enigma_analysis::find_ring_settings(cipher_text, rotor_configurations[0], bigram_fitness);

    std::cout << "Best ring settings: " << rotor_and_ring_configuration.rings[0] << ' ' << rotor_and_ring_configuration.rings[1] << ' ' << rotor_and_ring_configuration.rings[2] << "\nCurrent decryption: " << enigma_t(rotor_and_ring_configuration).encrypt(cipher_text) << '\n';

    scored_enigma_key_t optimal_key = enigma_analysis::find_plugs(cipher_text, rotor_and_ring_configuration, 5, quadgram_fitness);

    std::cout << "Best plugboard: " << optimal_key.plugboard_str() << "\nFinal decryption: " << enigma_t(optimal_key).encrypt(cipher_text) << "\n\n";
    
    const std::chrono::time_point end_time = std::chrono::system_clock::now();
    
    std::cout << "Total execution time: " << (end_time - start_time).count() / 10000 << '\n';
}

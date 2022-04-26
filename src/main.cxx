#include "analysis\enigma_analysis.hxx"
#include "analysis\fitness\fitness_functions.hxx"
#include <chrono>
#include <iostream>

int main() {
    const std::chrono::time_point start_time = std::chrono::system_clock::now();

    // For those interested, these were the original settings
    // II V III / 7 4 19 / 12 2 20 / AF TV KO BL RW
    std::string cipher_text = "OZLUDYAKMGMXVFVARPMJIKVWPMBVWMOIDHYPLAYUWGBZFAFAFUQFZQISLEZMYPVBRDDLAGIHIFUJDFADORQOOMIZPYXDCBPWDSSNUSYZTJEWZPWFBWBMIEQXRFASZLOPPZRJKJSPPSTXKPUWYSKNMZZLHJDXJMMMDFODIHUBVCXMNICNYQBNQODFQLOGPZYXRJMTLMRKQAUQJPADHDZPFIKTQBFXAYMVSZPKXIQLOQCVRPKOBZSXIUBAAJBRSNAFDMLLBVSYXISFXQZKQJRIQHOSHVYJXIFUZRMXWJVWHCCYHCXYGRKMKBPWRDBXXRGABQBZRJDVHFPJZUSEBHWAEOGEUQFZEEBDCWNDHIAQDMHKPRVYHQGRDYQIOEOLUBGBSNXWPZCHLDZQBWBEWOCQDBAFGUVHNGCIKXEIZGIZHPJFCTMNNNAUXEVWTWACHOLOLSLTMDRZJZEVKKSSGUUTHVXXODSKTFGRUEIIXVWQYUIPIDBFPGLBYXZTCOQBCAHJYNSGDYLREYBRAKXGKQKWJEKWGAPTHGOMXJDSQKYHMFGOLXBSKVLGNZOAXGVTGXUIVFTGKPJU";
    
    std::vector<scored_enigma_key> rotor_configurations = enigma_analysis::find_rotor_configuration(cipher_text, enigma_analysis::available_rotors::FIVE, {}, 10, ioc_fitness);

    std::cout << "\nTop 10 rotor configurations:\n";
    for (scored_enigma_key& sek : rotor_configurations) {
        std::cout << rotor(sek.rotors[0]).get_name() << ' ' << rotor(sek.rotors[1]).get_name() << ' ' << rotor(sek.rotors[2]).get_name() << " / " << sek.indicators[0] << ' ' << sek.indicators[1] << ' ' << sek.indicators[2] << " / " << sek.score << '\n';
    }
    std::cout << "Current decryption: " << enigma(rotor_configurations[0]).encrypt(cipher_text) << '\n';

    const std::chrono::time_point end_time = std::chrono::system_clock::now();
    
    std::cout << "Total execution time: " << (end_time - start_time).count() / 10000 << '\n';
}

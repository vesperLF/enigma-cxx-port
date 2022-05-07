#include "CppUnitTest.h"
#include "enigma\enigma.hxx"
#include <chrono>
#include <random>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(enigma_test) {
public:
    TEST_METHOD(encrypt_test) {
        //Basic settings
        enigma_t e = { {"I", 0, 0}, {"II", 0, 0}, {"III", 0, 0}, 'B', {}};
        const std::string input_short = "ABCDEFGHIJKLMNOPQRSTUVWXYZAAAAAAAAAAAAAAAAAAAAAAAAAABBBBBBBBBBBBBBBBBBBBBBBBBBABCDEFGHIJKLMNOPQRSTUVWXYZ";
        const std::string output_basic = "BJELRQZVJWARXSNBXORSTNCFMEYHCXTGYJFLINHNXSHIUNTHEORXOPLOVFEKAGADSPNPCMHRVZCYECDAZIHVYGPITMSRZKGGHLSRBLHL";
        Assert::AreEqual(output_basic, e.encrypt(input_short));

        //Varied rotors
        e = { {"VII", 10, 1}, {"V", 5, 2}, {"IV", 12, 3}, 'B', {}};
        const std::string output_varied = "FOTYBPKLBZQSGZBOPUFYPFUSETWKNQQHVNHLKJZZZKHUBEJLGVUNIOYSDTEZJQHHAOYYZSENTGXNJCHEDFHQUCGCGJBURNSEDZSEPLQP";
        Assert::AreEqual(output_varied, e.encrypt(input_short));

        //Long input
        e = { {"III", 3, 11}, {"VI", 5, 13}, {"VIII", 9, 19}, 'B', {}};
        const std::string input_long(500, 'A');
        const std::string output_long = "YJKJMFQKPCUOCKTEZQVXYZJWJFROVJMWJVXRCQYFCUVBRELVHRWGPYGCHVLBVJEVTTYVMWKJFOZHLJEXYXRDBEVEHVXKQSBPYZN"
            "IQDCBGTDDWZQWLHIBQNTYPIEBMNINNGMUPPGLSZCBRJULOLNJSOEDLOBXXGEVTKCOTTLDZPHBUFKLWSFSRKOMXKZELBDJNRUDUCO"
            "TNCGLIKVKMHHCYDEKFNOECFBWRIEFQQUFXKKGNTSTVHVITVHDFKIJIHOGMDSQUFMZCGGFZMJUKGDNDSNSJKWKENIRQKSUUHJYMIG"
            "WWNMIESFRCVIBFSOUCLBYEEHMESHSGFDESQZJLTORNFBIFUWIFJTOPVMFQCFCFPYZOJFQRFQZTTTOECTDOOYTGVKEWPSZGHCTQRP"
            "GZQOVTTOIEGGHEFDOVSUQLLGNOOWGLCLOWSISUGSVIHWCMSIUUSBWQIGWEWRKQFQQRZHMQJNKQTJFDIJYHDFCWTHXUOOCVRCVYOHL";
        Assert::AreEqual(output_long, e.encrypt(input_long));
    }
    TEST_METHOD(decrypt_test) {
#pragma warning(disable:4244)
        std::mt19937 random_generator(std::chrono::system_clock::now().time_since_epoch().count());
#pragma warning(default:4244)

        const std::string all_rotors[] = {
            "I",
            "II",
            "III",
            "IV",
            "V",
            "VI",
            "VII",
            "VIII"
        };

        std::string input(1000, ' ');
        for (char& c : input) {
            c = random_generator() % 26 + 65;
        }

        for (int test_count = 0; test_count < 10; test_count++) {
            std::string rotors[] = {
                all_rotors[random_generator() % 8],
                all_rotors[random_generator() % 8],
                all_rotors[random_generator() % 8]
            };

            int starting_positions[] = {
                random_generator() % 26,
                random_generator() % 26,
                random_generator() % 26
            };
            int ring_settings[] = {
                random_generator() % 26,
                random_generator() % 26,
                random_generator() % 26
            };

            enigma_t e1 = { {rotors[0], starting_positions[0], ring_settings[0]}, {rotors[1], starting_positions[1], ring_settings[1]}, {rotors[2], starting_positions[2], ring_settings[2]}, 'B', {}};//Encryption
            enigma_t e2 = { {rotors[0], starting_positions[0], ring_settings[0]}, {rotors[1], starting_positions[1], ring_settings[1]}, {rotors[2], starting_positions[2], ring_settings[2]}, 'B', {}};//Decryption

            Assert::AreEqual(input, e2.encrypt(e1.encrypt(input)));
        }
    }
    TEST_METHOD(plugboard_test) {
        //Simple test - 4 plugs
        enigma_t e = { {"I", 0, 0}, {"II", 0, 0}, {"III", 0, 0}, 'B', plugboard_t("AC FG JY LW") };
        const std::string input_4(50, 'A');
        const std::string output_4 = "QREBNMCYZELKQOJCGJVIVGLYEMUPCURPVPUMDIWXPPWROOQEGI";
        Assert::AreEqual(output_4, e.encrypt(input_4));

        //6 plugs
        e = { {"IV", 0, 0}, {"VI", 10, 0}, {"III", 6, 0}, 'B', plugboard_t("BM DH RS KN GZ FQ") };
        const std::string input_6 = "WRBHFRROSFHBCHVBENQFAGNYCGCRSTQYAJNROJAKVKXAHGUZHZVKWUTDGMBMSCYQSKABUGRVMIUOWAPKCMHYCRTSDEYTNJLVWNQY";
        const std::string output_6 = "FYTIDQIBHDONUPAUVPNKILDHDJGCWFVMJUFNJSFYZTSPITBURMCJEEAMZAZIJMZAVFCTYTKYORHYDDSXHBLQWPJBMSSWIPSWLENZ";
        Assert::AreEqual(output_6, e.encrypt(input_6));

        //10 plugs
        e = { {"I", 0, 5}, {"II", 1, 5}, {"III", 20, 4}, 'B', plugboard_t("AG HR YT KI FL WE NM SD OP QJ") };
        const std::string input_10 = "RNXYAZUYTFNQFMBOLNYNYBUYPMWJUQSBYRHPOIRKQSIKBKEKEAJUNNVGUQDODVFQZHASHMQIHSQXICTSJNAUVZYIHVBBARPJADRH";
        const std::string output_10 = "CFBJTPYXROYGGVTGBUTEBURBXNUZGGRALBNXIQHVBFWPLZQSCEZWTAWCKKPRSWOGNYXLCOTQAWDRRKBCADTKZGPWSTNYIJGLVIUQ";
        Assert::AreEqual(output_10, e.encrypt(input_10));
    }
};

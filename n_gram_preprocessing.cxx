#include <cmath>
#include <fstream>
#include <string>

const float epsilon = 3e-10f;
float singles[26];
float bigrams[826];
float quadgrams[845626];
float trigrams[26426];

int main() {
    std::string line;
    
    for (int i = 0; i < 26; i++) {
        singles[i] = log10(epsilon);
    }
    {
        std::ifstream single_file("resources\\data\\single");
        while (single_file) {
            std::getline(single_file, line);
            if (!line.empty()) {
                int i = line[0] - 65;
                singles[i] = std::stof(line.substr(line.find(',') + 1));
            }
        }
    }
    
    for (int i = 0; i < 826; i++) {
        bigrams[i] = log10(epsilon);
    }
    {
        std::ifstream bigrams_file("resources\\data\\bigrams");
        while (bigrams_file) {
            std::getline(bigrams_file, line);
            if (!line.empty()) {
                int i = ((line[0] - 65) << 5) | (line[1] - 65);
                bigrams[i] = std::stof(line.substr(line.find(',') + 1));
            }
        }
    }
    
    for (int i = 0; i < 26426; i++) {
        trigrams[i] = log10(epsilon);
    }
    {
        std::ifstream trigrams_file("resources\\data\\trigrams");
        while (trigrams_file) {
            std::getline(trigrams_file, line);
            if (!line.empty()) {
                int i = ((line[0] - 65) << 10) | ((line[1] - 65) << 5) | (line[2] - 65);
                trigrams[i] = std::stof(line.substr(line.find(',') + 1));
            }
        }
    }
    
    for (int i = 0; i < 845626; i++) {
        quadgrams[i] = log10(epsilon);
    }
    {
        std::ifstream quadgrams_file("resources\\data\\quadgrams");
        while (quadgrams_file) {
            std::getline(quadgrams_file, line);
            if (!line.empty()) {
                int i = ((line[0] - 65) << 15) | ((line[1] - 65) << 10) | ((line[2] - 65) << 5) | (line[3] - 65);
                quadgrams[i] = std::stof(line.substr(line.find(',') + 1));
            }
        }
    }
    
    std::ofstream out_file("src\\n_grams_data.cxx");
    out_file.precision(23);
    out_file << "#include n_grams_data.hxx\n\nconst float singles[26] = {\n";
    for (int i = 0; i < 25; i++) {
        out_file << '\t' << singles[i] << "f,\n";
    }
    out_file << '\t' << singles[25] << "f\n};\n\nconst float bigrams[826] = {\n";
    for (int i = 0; i < 825; i++) {
        out_file << '\t' << bigrams[i] << "f,\n";
    }
    out_file << '\t' << bigrams[825] << "f\n};\n\nconst float trigrams[26426] = {\n";
    for (int i = 0; i < 26425; i++) {
        out_file << '\t' << trigrams[i] << "f,\n";
    }
    out_file << '\t' << trigrams[26425] << "f\n};\n\nconst float quadgrams[845626] = {\n";
    for (int i = 0; i < 845625; i++) {
        out_file << '\t' << quadgrams[i] << "f,\n";
    }
    out_file << '\t' << quadgrams[845625] << "f\n};\n";
}

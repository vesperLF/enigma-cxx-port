# C++ Enigma

This is a C++ implementation of an Enigma machine, along with code that attempts to break the encryption. This code is associated with the Computerphile video on [cracking enigma](https://www.youtube.com/watch?v=RzWB5jL5RX0), and Mike's original Java implementation can be found [here](https://github.com/mikepound/enigma).

An enigma machine is a mechanical encryption device that saw a lot of use before and during WW2. This code simulates a 3 rotor enigma, including the 8 rotors commonly seen during the war. 

## Installing and Usage
You can compile and run this code yourself if you have a C++ compiler installed. For convenience I recommend using [Visual Studio](https://visualstudio.microsoft.com/) or a similar IDE. The community edition is free, and it'll make editing, compiling and running the code a lot easier. If you'd like to run it yourself, follow the instructions below. This assumes you've installed git.

### Windows
Clone and traverse into the enigma directory
```
git clone https://github.com/vesperLF/enigma-cxx-port.git
cd enigma-cxx-port
```

Open the solution file
```
.\enigma.sln
```

Use Visual Studio's GUI to compile and run

### Linux/Unix
I am not in the habit of using Linux at the moment, so I'm not going to test my code on Linux at this time.

## The Enigma Machine
The code for the enigma machine can be found in the `enigma` folder. In the `analysis` folder is the code to perform attacks on ciphertext. The attack uses various fitness functions that attempt to measure the effectiveness of a test decryption, found within the `analysis\fitness` folder. Finally, the `main.cxx` file is where you'll find the actual attack Mike performed in the video, and so it also contains a lot of examples you can use to run your own attacks.

### Creating a C++ Enigma
The code itself is fairly straightforward. You can create a new enigma machine using a constructor, for example this code will create a new object called `enigma_machine` with the settings provided:

```c++
enigma_t enigma_machine = {{"VII", 10, 1}, {"V", 5, 2}, {"IV", 12, 3}, 'B', "AD FT WH JO PN"};
```

Rotors and the reflector are given by their common names used in the war, with rotors labelled as `"I"` through to `"VIII"`, and reflectors `"B"` and `"C"`. Neither Mike nor I have implemented every variant, such as the thin reflectors seen in naval 4-rotor enigma. You could easily add these if you liked. Starting positions and ring settings are given as integers 0-25 rather than the A-Z often seen, this is just to avoid unnecessary mappings. The majority of the code here treats letters as 0-25 to aid indexing. Plugs are given as a string of character pairs representing steckered partners. If you don't wish to use a plugboard, `{}` is fine.

### Encrypting and Decrypting
Given an enigma instance like the `enigma_machine` above, encryption or decryption is performed on character arrays of capital letters [A-Z]. Simply to save time there has not been a lot of defensive coding to remove invalid characters, so be careful to only use uppercase, or to strip unwanted characters out of strings. Here is an encryption example using the enigma machine above:

```c++
std::string plaintext = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
std::string ciphertext = enigma_machine.encrypt(plaintext); // UJFZBOKXBAQSGCLDNUTSNTASEF
```
You can quickly check everything is working by running the tests found in the `enigma_test.cxx` file.

### How it works
Throughout the enigma machine, letters A-Z are represented as integers 0-25. Most of the components, the rotors, reflector and plugboard are treated as arrays that map values 0-25 to a different set of values 0-25. Encrypting or decrypting is simply a case of passing a value through these arrays in turn. What makes enigma trickier is that the arrays rotate, and that they can have different starting or ring positions. For efficiency in this implementation the arrays are fixed, and simulate rotation by shifting the index in and out of each rotor. Before each character is encrypted the rotors rotate, sometimes causing the neighbouring rotors to also rotate, this is handled by the `rotate()` function. Enigma has a quirk whereby the middle rotors moves twice when it turns the left-most rotor. This is called double stepping, and is also implemented here.

## Breaking a Code
Breaking an enigma message here comes down to decrypting a ciphertext with all possible rotor configurations and seeing which output looks the best. We measure best here using a fitness function.

### Fitness functions
The code makes a number of fitness functions available that can be used to measure how close a test decryption is to English text. Each works similarly, some work better than others. You can test to see which work best for a given message. The fitness functions are:
* **Index of coincidence**. The probability of any random two letters being identical. Tends to be higher for proper sentences than for random encrypted text. Mike's found this is quite good as an initial fitness function when there are many plugs involved.
* **Single / Bi / Tri / Quad grams**. The probability of a sentence measured based on the probability of constituent sequences of characters. Bigrams are pairs, such as AA or ST. Trigrams are triplets, e.g. THE, and so on. The more letters you use, e.g. single -> bi -> tri -> quad seems to improve the power of the fitness function, but you can't rely on this. Mike's found the longer measures are better when you already have some of the settings correct.
* **Plaintext Fitness**. This function is a known plaintext attack, comparing the decryption against all or portions of a suspected real plaintext. This is by far the most effective solution, even a few words of known plaintext will substantially increase your odds of a break even with a number of plugboard swaps. This fitness function has two overloads:
```c++
float known_plaintext_fitness(const char* text, const char* known_text)
```
Use this if you have an entire complete plaintext you're looking for.

```c++
float known_plaintext_fitness(const char* text, const std::vector<std::pair<std::string, size_t>>& word_offset_pairs)
```
This one takes pairs of words and their possible positions within the plaintext. For example, in the string "tobeornottobethatisthequestion" you might supply {"to", "that", "question"} and {0, 13, 22}. This function is used if you can guess some words, but aren't sure of the whole sentence, such as when you have partially broken the message already. Note that in the default example known plaintext won't improve much, because the attack is already successful. The errors in the output are not due to the fitness function, rather that we are not simultaneously pairing rotors and ring settings.

### Ciphertext Analysis
The basic approach to the attack is as follows:
1. Decrypt the ciphertext with every possible rotor in each position, and rotated to each starting position. All rotor ring settings are set to 0. No plugboard. For each decryption, measure the text fitness using one of the available fitness functions. Save the best performing rotor configuration.
2. Fix the rotors, and iterate through all possible ring settings for the middle and right rotors, again testing the fitness of the decryption. You do not have to use the same fitness function as before.
3. Fix all settings, and then use a hill climbing approach to find the best performing plugboard swaps, again measured using a fitness function.

## Notes
* The code is fairly efficient, Enigma boils down to a lot of array indexing into different rotors. I tried to optimize a bit more than Mike did, but it isn't really important. On my machine, the code completes in roughly 16 seconds for C++ release mode and 20 seconds for Java. C++ debug mode is far slower.
* Mike's added a more optimised and multi-threaded version in a branch called [optimised](https://github.com/mikepound/enigma/tree/optimised). While he's managed to get the code to break a message in under 4 seconds on a fast machine, I'm satisfied with just porting the original branch to C++.
* Similarly, in the brute force key search code, for simplicity new enigma machines are created as required rather than implementing a number of specific reinitialisation functions that would be faster.
* There isn't any kind of command line parsing here. You're welcome to add this, but for a tutorial on enigma and breaking it, a step by step procedure in main was fine.

## Resources
1. For more details on enigma, the [wikipedia articles](https://en.wikipedia.org/wiki/Enigma_machine) are a great resource.

2. This attack is a variant of that originally proposed by James Gillogly. His work on this is still available via the web archive [here](https://web.archive.org/web/20060720040135/http://members.fortunecity.com/jpeschel/gillog1.htm).

3. If you'd like a more visual example of both encryption and cracking enigma codes, the Cryptool project is a great tool for this. [Cryptool 2](https://www.cryptool.org/en/) has a great visualiser and can run cracking code similar to my own. I used cryptool to write the tests I used to make sure my own enigma implementation was working.

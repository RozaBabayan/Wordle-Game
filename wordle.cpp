// For debugging
#include <iostream>
// For std::remove
#include "dict-eng.h"
#include "wordle.h"
#include <algorithm>
#include <map>
#include <set>

using namespace std;
void wordleHelper(
        std::string word,
        const std::string& in,
        std::set<std::string>& result,
        const std::set<std::string>& dict,
        std::string f_letters,
        const char Letters[],
        long unsigned int len,
        long unsigned int dash);
bool isValid(std::string word, const std::set<std::string>& dict);

std::set<std::string> wordle(const std::string& in, const std::string& floating, const std::set<std::string>& dict) {

    char Letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
                        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    std::string f_letters = floating;
    std::set<std::string> result;
    long unsigned int dash = 0;  // keep track of number of '-'
    long unsigned int i = 0;
    while (i < in.size()) {
        if (in[i] == '-') {
            dash++;
        }
        i++;
    }

    wordleHelper("", in, result, dict, f_letters, Letters, 0, dash);
    return result;
}
void wordleHelper(
        std::string word,
        const std::string& in,
        std::set<std::string>& result,
        const std::set<std::string>& dict,
        std::string f_letters,
        const char Letters[],
        long unsigned int len,
        long unsigned int dash) {
    if (word.size() != in.size()) {
        // recursive case
        if (in[len] != '-') {
            wordleHelper(word + in[len], in, result, dict, f_letters, Letters, len + 1, dash);

        } else {
            // found a '-', need to replace it with a character either from floating letters or from any letter from
            // alphabet
            if (dash == f_letters.size()) {  // fill in a slot from a given floating letters and then iterate
                                             // through all the floating letters
                for (long unsigned int index = 0; index < f_letters.size(); index++) {
                    std::string newfloating = f_letters.substr(0, index) + f_letters.substr(index + 1);

                    wordleHelper(word + f_letters[index], in, result, dict, newfloating, Letters, len + 1, dash - 1);
                }
            } else if (dash != f_letters.size()) {  // fill in any remaining slots from  a letter from letters[]
                for (int l = 0; l < 26; l++) {
                    int idx = f_letters.find(Letters[l]);
                    if (idx < 0) {
                        wordleHelper(
                                word + Letters[l], in, result, dict, f_letters, Letters, len + 1, dash - 1);  //-i-- dn

                    } else if (idx >= 0) {

                        std::string newfloating = f_letters.substr(0, idx) + f_letters.substr(idx + 1);
                        wordleHelper(word + Letters[l], in, result, dict, newfloating, Letters, len + 1, dash - 1);
                    }
                }
            }
        }
    } else if (word.size() == in.size()) {  // base case
        if (isValid(word, dict)) {
            result.insert(word);
            return;
        }
    }
}

// check if it's a valid word
bool isValid(std::string word, const std::set<std::string>& dict) {
    std::set<std::string>::const_iterator it;
    if ((it = dict.find(word)) == dict.end()) {
        return false;
    }
    return true;
}
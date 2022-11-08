#pragma once

#ifndef WORDLE_WORDLE_PLAYER_H
#define WORDLE_WORDLE_PLAYER_H

#include "../_common/word_dict.h"

// Conform FirstGuessAnalyzer (08.11.2022) cuvantul cu cea mai mare entropie este:
// TAREI (6.41381)
const std::string FIRST_GUESS = "TAREI";

class wordle_player
{
private:
    const word_dict& dictionary;
    bool dump;
    int number_of_guesses;
    std::vector<std::string> second_guesses;
    int _patterncodecache = -1;

public:
    explicit wordle_player(const word_dict& dict, bool dump = false, bool use_second_guess_cache = true)
        : dictionary(dict), dump(dump)
    {
        number_of_guesses = 0;
        if (use_second_guess_cache) this->load_second_guess_cache();
        this->reset();
    }

    std::vector<std::string> words_list;

    void load_second_guess_cache();
    void reset();
    std::string get_best_guess();
    void apply_guess(const std::string& word, int pattern_code);
};

#endif //WORDLE_WORDLE_PLAYER_H

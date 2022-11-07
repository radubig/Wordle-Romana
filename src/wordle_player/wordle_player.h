#pragma once

#ifndef WORDLE_WORDLE_PLAYER_H
#define WORDLE_WORDLE_PLAYER_H

#include "../_common/word_dict.h"

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
    explicit wordle_player(const word_dict& dict, bool dump = false)
        : dictionary(dict), dump(dump)
    {
        number_of_guesses = 0;
        this->Load2ndGuessCache();
        this->reset();
    }

    std::vector<std::string> words_list;

    void Load2ndGuessCache();
    void reset();
    std::string get_best_guess();
    void apply_guess(const std::string& word, int pattern_code);
};

#endif //WORDLE_WORDLE_PLAYER_H

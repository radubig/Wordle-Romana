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

public:
    explicit wordle_player(const word_dict& dict, bool dump = false)
        : dictionary(dict), dump(dump)
    {
        this->reset();
    }

    std::vector<std::string> words_list;

    void reset();
    std::string get_best_guess();
    void apply_guess(const std::string& word, int pattern_code);
};

#endif //WORDLE_WORDLE_PLAYER_H

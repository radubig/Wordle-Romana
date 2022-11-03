#pragma once

#ifndef WORDLE_WORDLE_PLAYER_H
#define WORDLE_WORDLE_PLAYER_H

#include "../common/word_dict.h"

class wordle_player
{
private:
    const word_dict& dictionary;
    std::vector<std::string> words_list;

    void update(const std::string& guessed_word, int word_pattern);
    std::string analyze();

public:
    explicit wordle_player(const word_dict& dict) : dictionary(dict) { }
    void run();
};

#endif //WORDLE_WORDLE_PLAYER_H

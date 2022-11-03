#pragma once

#ifndef WORDLE_WORDLE_GAME_H
#define WORDLE_WORDLE_GAME_H

#include <iostream>

#include "../_common/word_dict.h"

class wordle_game
{
private:
    const word_dict& dictionary;
    std::string target;

public:
    explicit wordle_game(const word_dict& dict) : dictionary(dict) { }
    void reset(const std::string& forceWord = "");
    int guess(const std::string& word);
};

#endif //WORDLE_WORDLE_GAME_H

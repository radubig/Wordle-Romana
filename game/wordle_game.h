#pragma once

#ifndef WORDLE_WORDLE_GAME_H
#define WORDLE_WORDLE_GAME_H

#include <iostream>

#include "../common/word_dict.h"

using namespace std;

class wordle_game
{
private:
    const word_dict& dictionary;

public:
    explicit wordle_game(const word_dict& dict) : dictionary(dict) { }
    void play(const string& forceCuv = "");
};

#endif //WORDLE_WORDLE_GAME_H

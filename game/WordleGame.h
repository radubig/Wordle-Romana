#pragma once

#ifndef WORDLE_WORDLEGAME_H
#define WORDLE_WORDLEGAME_H

#include "../common/wordle_dict.h"
#include <iostream>

using std::string;

class WordleGame
{
private:
    const wordle_dict& dictionary;

public:
    explicit WordleGame(const wordle_dict& dict)
        :dictionary(dict) {}
    void play(const string& forceCuv = "");
};
#endif //WORDLE_WORDLEGAME_H

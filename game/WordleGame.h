#pragma once

#ifndef WORDLE_WORDLEGAME_H
#define WORDLE_WORDLEGAME_H

#include "../common/WordleDict.h"
#include <iostream>

using std::string;

class WordleGame
{
private:
    const WordleDict& dictionary;

public:
    explicit WordleGame(const WordleDict& dict)
        :dictionary(dict) {}
    void play(const string& forceCuv = "");
};
#endif //WORDLE_WORDLEGAME_H

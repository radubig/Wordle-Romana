#pragma once

#ifndef WORDLE_WORDLEPLAYER_H
#define WORDLE_WORDLEPLAYER_H

#include "WordleDict.h"

class WordlePlayer
{
private:
    const WordleDict& dictionary;
    std::vector<string> words_list;

    void update(const string& guessed_word, int word_pattern);
    string analyze();

public:
    explicit WordlePlayer(const WordleDict& dict)
        :dictionary(dict) {}
    void run();
};


#endif //WORDLE_WORDLEPLAYER_H

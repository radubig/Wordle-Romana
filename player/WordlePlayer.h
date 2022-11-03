#pragma once

#ifndef WORDLE_WORDLEPLAYER_H
#define WORDLE_WORDLEPLAYER_H

#include "../common/word_dict.h"

class WordlePlayer
{
private:
    const word_dict& dictionary;
    std::vector<string> words_list;

    void update(const string& guessed_word, int word_pattern);
    string analyze();

public:
    explicit WordlePlayer(const word_dict& dict)
        :dictionary(dict) {}
    void run();
};


#endif //WORDLE_WORDLEPLAYER_H

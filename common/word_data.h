#pragma once

#ifndef WORDLE_WORD_DATA_H
#define WORDLE_WORD_DATA_H

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct word_data
{
    string word;
    double entropy;

//    word_data() = default;
    word_data(const string& _word, double _entropy)
    {
        word = _word;
        entropy = _entropy;
    }

    bool operator >(const word_data& other) const
    {
        return entropy > other.entropy || (entropy == other.entropy && word < other.word);
    }
};

#endif //WORDLE_WORD_DATA_H

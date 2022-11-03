#pragma once

#ifndef WORDLE_WORDDATA_H
#define WORDLE_WORDDATA_H

#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

struct WordData
{
    string word;
    double entropy;

//    WordData() = default;
    WordData(const string& _word, double _entropy)
    {
        word = _word;
        entropy = _entropy;
    }

    bool operator >(const WordData& other) const
    {
        return entropy > other.entropy || (entropy == other.entropy && word < other.word);
    }
};

#endif //WORDLE_WORDDATA_H

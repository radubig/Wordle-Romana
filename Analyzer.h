#pragma once

#ifndef WORDLE_ANALYZER_H
#define WORDLE_ANALYZER_H

#include "WordleDict.h"

struct AData
{
    string word;
    double entropy;

    AData() = default;
    AData(const string& _word, const double& _entropy)
    {
        word = _word;
        entropy = _entropy;
    }

    bool operator > (const AData& other) const
    {
        if(entropy > other.entropy) return true;
        else if(entropy == other.entropy && word < other.word) return true;
        return false;
    }
};

class Analyzer {
private:
    const WordleDict& dictionary;

public:
    explicit Analyzer(const WordleDict& dict)
        :dictionary(dict) {}
    void run();
};


#endif //WORDLE_ANALYZER_H

#pragma once

#ifndef WORDLE_WORDLEDICT_H
#define WORDLE_WORDLEDICT_H

#include <string>
#include <unordered_set>
#include <vector>
using std::string;

class WordleDict {
private:
    string file;
    uint32_t dictSize; //Asta e hint

public:
    std::unordered_set<string> cuvinte;
    std::vector<string> vcuvinte;

    WordleDict(const string& fisier, uint32_t dictSz = 0)
        :file(fisier), dictSize(dictSz) {}
    void init();
    void clear();
};


#endif //WORDLE_WORDLEDICT_H

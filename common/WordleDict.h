#pragma once

#ifndef WORDLE_WORDLEDICT_H
#define WORDLE_WORDLEDICT_H

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class WordleDict {
private:
    string file;

public:
    unordered_set<string> cuvinte;
    vector<string> vcuvinte;

    explicit WordleDict(string fisier) :file(std::move(fisier)) { }
    void init();
    void clear();
};

#endif //WORDLE_WORDLEDICT_H

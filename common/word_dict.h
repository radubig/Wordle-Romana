#pragma once

#ifndef WORDLE_WORD_DICT_H
#define WORDLE_WORD_DICT_H

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class word_dict
{
private:
    string file;

public:
    unordered_set<string> cuvinte;
    vector<string> vcuvinte;

    explicit word_dict(string fisier) : file(std::move(fisier)) { }
    void init();
    void clear();
};

#endif //WORDLE_WORD_DICT_H

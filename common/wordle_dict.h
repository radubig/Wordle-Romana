#pragma once

#ifndef WORDLE_WORDLE_DICT_H
#define WORDLE_WORDLE_DICT_H

#include <string>
#include <unordered_set>
#include <vector>

using namespace std;

class wordle_dict {
private:
    string file;

public:
    unordered_set<string> cuvinte;
    vector<string> vcuvinte;

    explicit wordle_dict(string fisier) : file(std::move(fisier)) { }
    void init();
    void clear();
};

#endif //WORDLE_WORDLE_DICT_H

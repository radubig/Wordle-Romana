#pragma once

#ifndef WORDLE_WORD_DICT_H
#define WORDLE_WORD_DICT_H

#include <string>
#include <unordered_set>
#include <vector>

class word_dict
{
private:
    std::string file;

public:
    std::unordered_set<std::string> cuvinte;
    std::vector<std::string> vcuvinte;

    explicit word_dict(std::string fisier) : file(std::move(fisier)) { }
    void init();
};

#endif //WORDLE_WORD_DICT_H

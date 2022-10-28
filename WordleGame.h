#pragma once

#ifndef WORDLE_WORDLEGAME_H
#define WORDLE_WORDLEGAME_H

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
using std::string;

class WordleGame
{
private:
    string file;
    uint32_t dictSize;
    
    std::unordered_set<string> cuvinte;
    std::vector<string> vcuvinte;
    string word;

public:
    explicit WordleGame(const string& fisier, uint32_t dictSz = 0) 
    {
        file = fisier;
        dictSize = dictSz;
    }
    void init();
    void play(const string& forceCuv = "");
    void clear();
};
#endif //WORDLE_WORDLEGAME_H

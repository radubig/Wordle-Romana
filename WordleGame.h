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
    std::unordered_set<string> cuvinte;
    std::vector<string> vcuvinte;
    string word;

public:
    explicit WordleGame() {file = "cuvinte.txt";}
    explicit WordleGame(const string& fisier) {file = fisier;}
    void init();
    void play();
    void clear();
    void hint(uint32_t sz);
    void setfile(const string& src);
};
#endif //WORDLE_WORDLEGAME_H

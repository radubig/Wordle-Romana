#pragma once

#ifndef WORDLE_WORDLE_H
#define WORDLE_WORDLE_H

#include <string>

using namespace std;

#define encodePattern(data) 81 * data[0] + 27 * data[1] + 9 * data[2] + 3 * data[3] + data[4];

#define GRI 0
#define VERDE 1
#define GALBEN 2

class wordle
{
public:
    static int* getPattern(const string& target, const string& guess);
};

#endif //WORDLE_WORDLE_H

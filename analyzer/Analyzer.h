#pragma once

#ifndef WORDLE_ANALYZER_H
#define WORDLE_ANALYZER_H

#include "../common/WordleDict.h"

class Analyzer {
private:
    const WordleDict& dictionary;

public:
    explicit Analyzer(const WordleDict& dict) : dictionary(dict) {}
    void run();
};

#endif //WORDLE_ANALYZER_H

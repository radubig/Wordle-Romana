#pragma once

#ifndef WORDLE_ANALYZER_H
#define WORDLE_ANALYZER_H

#include "../common/word_dict.h"

class analyzer {
private:
    const word_dict& dictionary;

public:
    explicit analyzer(const word_dict& dict) : dictionary(dict) {}
    void run();
};

#endif //WORDLE_ANALYZER_H

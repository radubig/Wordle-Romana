#pragma once

#ifndef WORDLE_ANALYZER_H
#define WORDLE_ANALYZER_H

#include "../common/wordle_dict.h"

class analyzer {
private:
    const wordle_dict& dictionary;

public:
    explicit analyzer(const wordle_dict& dict) : dictionary(dict) {}
    void run();
};

#endif //WORDLE_ANALYZER_H

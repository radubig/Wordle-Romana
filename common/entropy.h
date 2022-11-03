#pragma once

#ifndef WORDLE_ENTROPY_H
#define WORDLE_ENTROPY_H

#include <vector>
#include "word_data.h"

class entropy
{
public:
    static std::vector<word_data>* calculate_entropy(const std::vector<std::string> &cuvinte);
};

#endif //WORDLE_ENTROPY_H

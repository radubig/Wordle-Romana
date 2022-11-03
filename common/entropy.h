#pragma once

#ifndef WORDLE_ENTROPY_H
#define WORDLE_ENTROPY_H

#include <vector>
#include "word_data.h"

class entropy
{
public:
    static std::vector<word_data> const& calculate_entropy(const std::vector<std::string> &dictionar, const std::vector<std::string> &cuvinteRamase);
};

#endif //WORDLE_ENTROPY_H

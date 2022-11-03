#pragma once

#ifndef WORDLE_PATTERNS_H
#define WORDLE_PATTERNS_H

#include <string>

#define GRAY 0
#define GREY GRAY // For the british
#define GREEN 1
#define YELLOW 2

#define NUM_PATTERNS 243 // 3 ^ 5
#define GUESSED_PATTERN 121

class patterns
{
public:
    static int* const& get_pattern(const std::string& target, const std::string& guess);
    static int encode_pattern(const int* status);
    static int* const& decode_pattern(int cod_p);
};

#endif //WORDLE_PATTERNS_H

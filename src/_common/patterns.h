#pragma once

#ifndef WORDLE_PATTERNS_H
#define WORDLE_PATTERNS_H

#include <string>

#define NUM_PATTERNS 243 // 3 ^ 5
#define GUESSED_PATTERN 121

class patterns
{
public:
    enum ptype
    {
        GRAY = 0,
        GREY = 0, // For the British
        GREEN = 1,
        YELLOW = 2
    };


    static int* get_pattern(const std::string& target, const std::string& guess);
    static int encode_pattern(const int* status);
    static int* decode_pattern(int cod_p);
};

#endif //WORDLE_PATTERNS_H

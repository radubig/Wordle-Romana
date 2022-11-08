#pragma once

#ifndef WORDLE_PATHS_H
#define WORDLE_PATHS_H

#include <string>

const std::string WORD_DICTIONARY_FILE_PATH = "cuvinte.txt";
const std::string FIRST_GUESS_FILE_PATH = "best_first_guess.txt";
const std::string SECOND_GUESS_FILE_PATH = "second_guess_cache.txt";
const std::string ENTROPY_DUMP_FILE_PATH = "entropy_dump.txt";
const std::string STATS_FILE_PATH = "stats.txt";

#endif //WORDLE_PATHS_H

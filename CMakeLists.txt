cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wordle_Analyzer analyzer/analyzer.cpp analyzer/analyzer.h analyzer/main.cpp common/word_dict.cpp common/word_dict.h common/word_data.h common/patterns.cpp common/patterns.h common/entropy.cpp common/entropy.h)
add_executable(Wordle_Game game/wordle_game.h game/wordle_game.cpp common/word_dict.cpp common/word_dict.h game/main.cpp common/word_data.h common/patterns.cpp common/patterns.h)
add_executable(Wordle_Player common/word_dict.h common/word_dict.cpp player/wordle_player.cpp player/wordle_player.h player/main.cpp common/word_data.h common/entropy.cpp common/entropy.h common/patterns.cpp common/patterns.h)

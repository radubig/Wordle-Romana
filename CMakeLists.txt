cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wordle_Analyzer analyzer/analyzer.cpp analyzer/analyzer.h analyzer/main.cpp common/word_dict.cpp common/word_dict.h common/word_data.h common/wordle.cpp common/wordle.h)
add_executable(Wordle_Game game/wordle_game.h game/wordle_game.cpp common/word_dict.cpp common/word_dict.h game/main.cpp common/word_data.h common/wordle.cpp common/wordle.h)
add_executable(Wordle_Player common/word_dict.h common/word_dict.cpp game/wordle_game.cpp game/wordle_game.h player/WordlePlayer.cpp player/WordlePlayer.h player/main.cpp common/word_data.h)

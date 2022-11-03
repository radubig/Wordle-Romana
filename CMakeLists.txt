cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wordle_Analyzer analyzer/analyzer.cpp analyzer/analyzer.h analyzer/main.cpp common/wordle_dict.cpp common/wordle_dict.h common/word_data.h common/pattern.h)
add_executable(Wordle_Game game/WordleGame.h game/WordleGame.cpp common/wordle_dict.cpp common/wordle_dict.h game/main.cpp common/word_data.h)
add_executable(Wordle_Player common/wordle_dict.h common/wordle_dict.cpp game/WordleGame.cpp game/WordleGame.h player/WordlePlayer.cpp player/WordlePlayer.h player/main.cpp common/word_data.h)

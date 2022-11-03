cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wordle_Analyzer analyzer/Analyzer.cpp analyzer/Analyzer.h analyzer/main.cpp common/WordleDict.cpp common/WordleDict.h common/WordData.h common/Pattern.h)
add_executable(Wordle_Game game/WordleGame.h game/WordleGame.cpp common/WordleDict.cpp common/WordleDict.h game/main.cpp common/WordData.h)
add_executable(Wordle_Player common/WordleDict.h common/WordleDict.cpp game/WordleGame.cpp game/WordleGame.h player/WordlePlayer.cpp player/WordlePlayer.h player/main.cpp common/WordData.h)

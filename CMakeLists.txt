cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

add_executable(Wordle main.cpp WordleGame.h WordleGame.cpp WordleDict.cpp WordleDict.h)

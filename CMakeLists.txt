cmake_minimum_required(VERSION 3.23)
project(Wordle)
enable_language(CXX ASM)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_FLAGS "-m32")
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_ASM_COMPILER gcc)
set(CMAKE_ASM_FLAGS "-m32 -no-pie -g")

find_package(Boost)
if(NOT Boost_FOUND)
    message(ERROR "boost library not found, install with \"sudo apt-get install libboost-all-dev\"")
endif()

include_directories(${Boost_INCLUDE_DIRS})

file(GLOB_RECURSE _Common "src/_common/*")

file(GLOB_RECURSE WordleGame "src/wordle_game/*")
list(FILTER WordleGame EXCLUDE REGEX "src/wordle_game/main.cpp")
add_executable(WordleGame src/wordle_game/main.cpp ${WordleGame} ${_Common})

file(GLOB_RECURSE WordlePlayer "src/wordle_player/*")
list(FILTER WordlePlayer EXCLUDE REGEX "src/wordle_player/main.cpp")
add_executable(WordlePlayer src/wordle_player/main.cpp ${WordlePlayer} ${_Common})

file(GLOB_RECURSE FirstGuessAnalyzer "src/first_guess_analyzer/*")
list(FILTER FirstGuessAnalyzer EXCLUDE REGEX "src/first_guess_analyzer/main.cpp")
add_executable(FirstGuessAnalyzer src/first_guess_analyzer/main.cpp ${FirstGuessAnalyzer} ${_Common})

file(GLOB_RECURSE SecondGuessAnalyzer "src/second_guess_analyzer/*")
list(FILTER SecondGuessAnalyzer EXCLUDE REGEX "src/second_guess_analyzer/main.cpp")
add_executable(SecondGuessAnalyzer src/second_guess_analyzer/main.cpp ${SecondGuessAnalyzer} ${WordlePlayer} ${_Common})

file(GLOB_RECURSE StatisticsGenerator "src/statistics_generator/*")
list(FILTER StatisticsGenerator EXCLUDE REGEX "src/statistics_generator/main.cpp")
add_executable(StatisticsGenerator src/statistics_generator/main.cpp ${StatisticsGenerator} ${WordleGame} ${WordlePlayer} ${_Common})

file(GLOB_RECURSE ASM__Common "src_asm/_common/*")

file(GLOB_RECURSE ASM_WordleGame "src_asm/wordle_game/*")
add_executable(ASM_WordleGame ${ASM_WordleGame} ${ASM__Common})

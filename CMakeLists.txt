cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE _Common "src/_common/*")

file(GLOB_RECURSE FirstGuessAnalyzer "src/first_guess_analyzer/*")
list(FILTER FirstGuessAnalyzer EXCLUDE REGEX "src/first_guess_analyzer/main.cpp")
add_executable(FirstGuessAnalyzer src/first_guess_analyzer/main.cpp ${FirstGuessAnalyzer} ${_Common})

file(GLOB_RECURSE WordleGame "src/wordle_game/*")
list(FILTER WordleGame EXCLUDE REGEX "src/wordle_game/main.cpp")
add_executable(WordleGame src/wordle_game/main.cpp ${WordleGame} ${_Common})

file(GLOB_RECURSE WordlePlayer "src/wordle_player/*")
list(FILTER WordlePlayer EXCLUDE REGEX "src/wordle_player/main.cpp")
add_executable(WordlePlayer src/wordle_player/main.cpp ${WordlePlayer} ${_Common})

file(GLOB_RECURSE StatisticsGenerator "src/statistics_generator/*")
list(FILTER StatisticsGenerator EXCLUDE REGEX "src/statistics_generator/main.cpp")
add_executable(StatisticsGenerator src/statistics_generator/main.cpp ${StatisticsGenerator} ${Game} ${Player} ${_Common})

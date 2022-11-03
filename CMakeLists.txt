cmake_minimum_required(VERSION 3.23)
project(Wordle)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE _Common "src/_common/*")

file(GLOB_RECURSE FirstGuessAnalyzer "src/first_guess_analyzer/*")
list(FILTER FirstGuessAnalyzer EXCLUDE REGEX "src/first_guess_analyzer/main.cpp")
add_executable(FirstGuessAnalyzer src/first_guess_analyzer/main.cpp ${FirstGuessAnalyzer} ${_Common})

file(GLOB_RECURSE Game "src/game/*")
list(FILTER Game EXCLUDE REGEX "src/game/main.cpp")
add_executable(Game src/game/main.cpp ${Game} ${_Common})

file(GLOB_RECURSE Player "src/player/*")
list(FILTER Player EXCLUDE REGEX "src/player/main.cpp")
add_executable(Player src/player/main.cpp ${Player} ${_Common})

file(GLOB_RECURSE StatisticsGenerator "src/statistics_generator/*")
list(FILTER StatisticsGenerator EXCLUDE REGEX "src/statistics_generator/main.cpp")
add_executable(StatisticsGenerator src/statistics_generator/main.cpp ${StatisticsGenerator} ${Game} ${Player} ${_Common})

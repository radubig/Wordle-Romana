#include "wordle_game.h"
#include "../_common/patterns.h"

using namespace std;

void wordle_game::reset(const string &forceWord)
{
    int indexCuv = rand() % dictionary.vcuvinte.size(); // NOLINT(cppcoreguidelines-narrowing-conversions,cert-msc50-cpp)
    target = dictionary.vcuvinte[indexCuv];

    if (!forceWord.empty()) target = forceWord;
}

int wordle_game::guess(const std::string &word)
{
    if (dictionary.cuvinte.find(word) == dictionary.cuvinte.end()) return -1;
    int* status = patterns::get_pattern(target, word);
    return patterns::encode_pattern(status);
}

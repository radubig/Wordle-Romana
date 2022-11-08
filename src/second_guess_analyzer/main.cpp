#include <fstream>
#include <iomanip>
#include <iostream>
#include "../_common/patterns.h"
#include "../_common/paths.h"
#include "../_common/word_dict.h"
#include "../wordle_player/wordle_player.h"
using namespace std;

int main()
{
    try
    {
        word_dict dict(WORD_DICTIONARY_FILE_PATH);
        dict.init();

        wordle_player player(dict, false, false);
        vector<string> generated_guesses;

        cout << "Te rog asteapta..." << endl;

        for (int i = 0; i < NUM_PATTERNS; i++)
        {
            if (i == GUESSED_PATTERN)
            {
                generated_guesses.push_back(FIRST_GUESS);
                continue;
            }
            player.reset();
            player.apply_guess(FIRST_GUESS, i);
            string guess = player.get_best_guess();
            generated_guesses.push_back(guess);
        }

        ofstream out(SECOND_GUESS_FILE_PATH);
        for(auto& i : generated_guesses)
            out << i << '\n';
        out.close();

        cout << "Rezultate salvate in " << SECOND_GUESS_FILE_PATH << endl;

        return 0;
    }
    catch (const runtime_error& e)
    {
        cerr << "A aparut o eroare." << endl;
        cerr << e.what();
        return -1;
    }
    catch (...)
    {
        cerr << "A aparut o eroare neasteptata." << endl;
        return -1;
    }
}

#include <fstream>
#include <iostream>
#include "../_common/patterns.h"
#include "../_common/word_dict.h"
#include "../game/wordle_game.h"
#include "../player/wordle_player.h"
using namespace std;

int main()
{
    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        wordle_game game(dict);
        wordle_player player(dict);
        
        int number_of_guesses[10] = {0};
        
        for (const string& word : dict.vcuvinte)
        {
            int guesses = 0;
            game.reset(word);
            player.reset();
            
            while (true)
            {
                guesses++;
                string guessed_word = player.get_best_guess();
                int pattern = game.guess(guessed_word);
                player.apply_guess(word, pattern);
                
                if (pattern == GUESSED_PATTERN) break;
            }
            
            number_of_guesses[guesses]++;
            
            if (guesses == 1)
                cout << "Cuvantul " << word << " a fost ghicit in 1 incercare.";
            else
                cout << "Cuvantul " << word << " a fost ghicit in " << guesses << " incercari.";
        }

        return 0;
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

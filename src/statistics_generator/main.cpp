#include <fstream>
#include <iomanip>
#include <iostream>
#include "../_common/patterns.h"
#include "../_common/word_dict.h"
#include "../wordle_game/wordle_game.h"
#include "../wordle_player/wordle_player.h"
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
        int total = 0;
        int sum = 0;
        
        cout << setprecision(2) << fixed;
        
        for (const string& current_word : dict.vcuvinte)
        {
            int guesses = 1;
            game.reset(current_word);
            player.reset();

            string guessed_word = "TAREI";
            int pattern = game.guess(guessed_word);
            player.apply_guess(guessed_word, pattern);
            
            cout << "Ghicire: " << guessed_word << " " << pattern << endl;
            cout << "Cuvinte posibile: ";
            for (const string& possible_word : player.words_list) cout << possible_word << " ";
            cout << endl;
            
            while (pattern != GUESSED_PATTERN)
            {
                guesses++;
                guessed_word = player.get_best_guess();
                pattern = game.guess(guessed_word);
                player.apply_guess(guessed_word, pattern);
                
                cout << "Ghicire: " << guessed_word << " " << pattern << endl;
                cout << "Cuvinte posibile: ";
                for (const string& possible_word : player.words_list) cout << possible_word << " ";
                cout << endl;
            }
            
            number_of_guesses[guesses]++;
            total++;
            sum += guesses;
            
            if (guesses == 1)
                cout << "Cuvantul " << current_word << " a fost ghicit in 1 incercare. (Media: " << (1.0 * sum / total) << ")" << endl;
            else
                cout << "Cuvantul " << current_word << " a fost ghicit in " << guesses << " incercari. (Media: " << (1.0 * sum / total) << ")" << endl;
        }
        
        ofstream fout("../stats.txt");
        for (int i = 1; i < 9; i++)
        {
            if (number_of_guesses[i] == 0 && number_of_guesses[i + 1] == 0) break;
            
            fout << i;
            if (i == 1) fout << " INCERCARE: ";
            else fout << " INCERCARI: ";
            
            fout << number_of_guesses[i] << "/" << total << " (" << setprecision(2) << (number_of_guesses[i] / total * 100) << "%)\n";
        }
        fout << "\nMEDIA: " << (1.0 * sum / total);
        fout.close();

        return 0;
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

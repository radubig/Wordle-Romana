#include <iostream>
#include "wordle_player.h"
#include "../_common/patterns.h"

using namespace std;

int main()
{
    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        wordle_player player(dict);
        player.reset();

        int guesses = 1;
        int in_pattern;

        // Conform entropy_list.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
        // TARIE (6.42526)
        string guess = "TARIE";

        cout << "Ghiceste: TARIE\n"
                "Introdu codul raspunsului: ";
        cin >> in_pattern;
        player.apply_guess(guess, in_pattern);
        cout << "Cuvinte posibile: ";
        for (const string& word : player.words_list) cout << word << " ";
        cout << endl;

        while (in_pattern != GUESSED_PATTERN)
        {
            guesses++;

            if (player.words_list.size() == 1)
            {
                cout << "Ghiceste: " << player.words_list[0] << "\n";
                cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
                return 0;
            }
            
            guess = player.get_best_guess();
            cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
            cin >> in_pattern;
            player.apply_guess(guess, in_pattern);
        }

        if (guesses == 1)
            cout << "Cuvant ghicit in 1 incercare.\n" << endl;
        else
            cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
        
        return 0;
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

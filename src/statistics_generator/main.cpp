#include <bits/stdc++.h>
#include "../_common/paths.h"
#include "../_common/patterns.h"
#include "../_common/word_dict.h"
#include "../wordle_game/wordle_game.h"
#include "../wordle_player/wordle_player.h"
#include "../_common/entropy.h"
using namespace std;

inline void Gen_Stats();
inline void First_Guess_Analyzer();
inline void Second_Guess_Analyzer();

int main()
{
    try
    {
        Gen_Stats();
        //First_Guess_Analyzer();
        //Second_Guess_Analyzer();
    }
    catch (const runtime_error& e)
    {
        cerr << "A aparut o eroare." << endl;
        cerr << e.what() << endl;
        return -1;
    }
    catch (...)
    {
        cerr << "A aparut o eroare neasteptata." << endl;
        return -1;
    }

    return 0;
}

inline void Gen_Stats()
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    wordle_game game(dict);
    wordle_player player(dict);

    int number_of_guesses[10] = {0};
    int total = 0;
    int sum = 0;

    cout << setprecision(2) << fixed;

    ofstream solutii(SOLVE_FILE_PATH);

    for (const string& current_word : dict.vcuvinte)
    {
        solutii << current_word << ": ";

        int guesses = 1;
        game.reset(current_word);
        player.reset();

        string guessed_word = FIRST_GUESS;
        int pattern = game.guess(guessed_word);
        player.apply_guess(guessed_word, pattern);

        solutii << guessed_word;

        while (pattern != GUESSED_PATTERN)
        {
            guesses++;
            guessed_word = player.get_best_guess();
            pattern = game.guess(guessed_word);
            player.apply_guess(guessed_word, pattern);

            solutii << ", " << guessed_word;
        }

        number_of_guesses[guesses]++;
        total++;
        sum += guesses;

        solutii << "\n";

        if (guesses == 1)
            cout << "Cuvantul " << current_word << " a fost ghicit in 1 incercare. (Media: " << (1.0 * sum / total) << ")" << endl;
        else
            cout << "Cuvantul " << current_word << " a fost ghicit in " << guesses << " incercari. (Media: " << (1.0 * sum / total) << ")" << endl;
    }

    solutii.close();

    ofstream fout(STATS_FILE_PATH);
    for (int i = 1; i < 9; i++)
    {
        if (number_of_guesses[i] == 0 && number_of_guesses[i + 1] == 0) break;

        fout << i;
        if (i == 1) fout << " INCERCARE: ";
        else fout << " INCERCARI: ";

        fout << number_of_guesses[i] << "/" << total << "\n";
    }
    fout << "\nMEDIA: " << (1.0 * sum / total);
    fout.close();
}

inline void First_Guess_Analyzer()
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    cout << "Te rog asteapta..." << endl;

    vector<word_data> ent_cuvinte = entropy::calculate_entropy(dict.vcuvinte, dict.vcuvinte);
    sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

    ofstream out(FIRST_GUESS_FILE_PATH);
    for (const word_data& i : ent_cuvinte)
    {
        out << i.word << " : " << i.entropy << "\n";
    }
    out.close();

    cout << "Rezultate salvate in " << FIRST_GUESS_FILE_PATH << endl;
}

inline void Second_Guess_Analyzer()
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
}

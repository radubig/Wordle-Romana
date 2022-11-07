#include <iostream>
#include "wordle_player.h"
#include "../_common/patterns.h"

using namespace std;

static void StandardPlay();
static void AutoPlay();

int main(int argc, char** argv)
{
    try
    {
        if(argc < 2)
        {
            StandardPlay();
        }
        else
        {
            AutoPlay();
        }
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }

    return 0;
}

inline static void StandardPlay()
{
    word_dict dict("cuvinte.txt");
    dict.init();

    wordle_player player(dict);
    //player.reset();

    int guesses = 1;
    int in_pattern;

    // Conform first_guess_entropy.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
    // TAREI (6.41381)
    string guess = FIRST_GUESS;

    cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
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
            return;
        }

        guess = player.get_best_guess();
        cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
        cin >> in_pattern;
        player.apply_guess(guess, in_pattern);
        cout << "Cuvinte posibile: ";
        for (const string& word : player.words_list) cout << word << " ";
        cout << endl;
    }

    if (guesses == 1)
        cout << "Cuvant ghicit in 1 incercare.\n" << endl;
    else
        cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
}

inline static void AutoPlay()
{
    word_dict dict("cuvinte.txt");
    dict.init();

    wordle_player player(dict);
    //player.reset();

    int guesses = 1;
    int in_pattern;

    // Conform first_guess_entropy.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
    // TAREI (6.41381)
    string guess = FIRST_GUESS;

    cin >> in_pattern;

    player.apply_guess(guess, in_pattern);

    while (in_pattern != GUESSED_PATTERN)
    {
        guesses++;

        if (player.words_list.size() == 1)
        {
            cout << "Ghiceste: " << player.words_list[0] << "\n";
            return;
        }

        guess = player.get_best_guess();

        cin >> in_pattern;
        player.apply_guess(guess, in_pattern);
    }

}

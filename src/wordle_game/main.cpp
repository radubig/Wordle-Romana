#include <boost/process.hpp>
#include <iostream>
#include "wordle_game.h"
#include "../_common/paths.h"
#include "../_common/patterns.h"

using namespace std;

static void StandardPlay();
static void AutoPlay();

int main(int argc, char** argv)
{
    try
    {
        if (argc < 2)
        {
            StandardPlay();
        }
        else
        {
            AutoPlay();
        }
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

    return 0;
}

inline static void StandardPlay()
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    wordle_game game(dict);

    cout << "Wordle: Incearca sa ghicesti un cuvant de 5 litere!\n"
            "Vei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\n"
            "Esti pregatit? Tasteaza un cuvant de 5 litere:" << endl;

    int pattern_code = -1;
    int guesses = 0;
    do
    {
        string guess;
        cin >> guess;

        if (guess.size() != 5)
        {
            cout << "Cuvantul introdus nu are 5 litere!\nIntrodu un alt cuvant:" << endl;
            continue;
        }

        bool isValid = true;
        for (char& c : guess)
        {
            if (c >= 'a' && c <= 'z')
            {
                c -= 32;
            }
            else if (c < 'A' || c > 'Z')
            {
                isValid = false;
                break;
            }
        }

        if (!isValid)
        {
            cout << "Cuvantul introdus contine si alte caractere in afara de litere!\nIntrodu un alt cuvant:" << endl;
            continue;
        }

        pattern_code = game.guess(guess);

        if (pattern_code == -1)
        {
            cout << "Cuvantul introdus nu face parte din dictionar!\nIntrodu un alt cuvant:" << endl;
            continue;
        }

        guesses++;
        int* pattern = patterns::decode_pattern(pattern_code);

        for (int i = 0; i < 5; i++)
        {
            if (pattern[i] == patterns::GREEN)
                cout << guess[i] << ": Corect!\n";
            else if (pattern[i] == patterns::YELLOW)
                cout << guess[i] << ": Alta pozitie!\n";
            else
                cout << guess[i] << ": Nu exista!\n";
        }

        cout << "Codul raspunsului: " << pattern_code << "\n" << endl;
        if (pattern_code != GUESSED_PATTERN) cout << "Introdu urmatorul cuvant: " << endl;
    } while (pattern_code != GUESSED_PATTERN);

    if (guesses == 1)
        cout << "FELICITARI! Ai ghicit cuvantul in 1 incercare!\n" << endl;
    else
        cout << "FELICITARI! Ai ghicit cuvantul in " << guesses << " incercari!\n" << endl;

}

inline static void AutoPlay()
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    wordle_game game(dict);
    //game.reset();

    int pattern_code = -1;
    int guesses = 0;
    do
    {
        string guess;
        cin >> guess;

        if (guess.size() != 5)
            throw runtime_error("Cuvantul ghicit " + guess + " nu are 5 litere!");

        bool isValid = true;
        for (char& c : guess)
        {
            if (c >= 'a' && c <= 'z')
            {
                c -= 32;
            }
            else if (c < 'A' || c > 'Z')
            {
                isValid = false;
                break;
            }
        }
        if (!isValid)
            throw runtime_error("Cuvantul ghicit " + guess + " este invalid!");

        pattern_code = game.guess(guess);
        if (pattern_code == -1)
            throw runtime_error("Cuvantul ghicit " + guess + " nu este in dictionar!");

        guesses++;
        cout << pattern_code << endl;

    } while (pattern_code != GUESSED_PATTERN);


}
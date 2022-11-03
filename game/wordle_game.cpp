#include <random>
#include "wordle_game.h"
#include "../common/patterns.h"

using namespace std;

void wordle_game::play(const string& forceCuv)
{
    string word;
    string guess;

    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    int indexCuv = rand() % dictionary.cuvinte.size(); // NOLINT(cppcoreguidelines-narrowing-conversions,cert-msc50-cpp)
    word = dictionary.vcuvinte[indexCuv];
    
    if (!forceCuv.empty()) word = forceCuv;

    cout << "Wordle: Incearca sa ghicesti un cuvant de 5 litere!\n"
            "Vei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\n"
            "Esti pregatit? Tasteaza un cuvant de 5 litere:" << endl;
    
    int incercari = 0;
    
    do
    {
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

        if (dictionary.cuvinte.find(guess) == dictionary.cuvinte.end())
        {
            cout << "Cuvantul introdus nu face parte din dictionar!\nIntrodu un alt cuvant:" << endl;
            continue;
        }

        incercari++;

        int* status = patterns::get_pattern(word, guess);

        for (int i=0; i<5; i++)
        {
            if (status[i] == GREEN)
                cout << guess[i] << ": Corect!\n";
            else if (status[i] == YELLOW)
                cout << guess[i] << ": Alta pozitie!\n";
            else
                cout << guess[i] << ": Nu exista!\n";
        }
        
        int cod_p = patterns::encode_pattern(status);
        
        cout << "Codul raspunsului: " << cod_p << "\n" << endl;
        cout << "Introdu urmatorul cuvant: " << endl;
    } while(guess != word);

    if (incercari == 1)
        cout << "FELICITARI! Ai ghicit cuvantul in 1 incercare!\n" << endl;
    else
        cout << "FELICITARI! Ai ghicit cuvantul in " << incercari << " incercari!\n" << endl;
}

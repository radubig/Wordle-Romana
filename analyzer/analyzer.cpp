#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>

#include "../common/pattern.h"
#include "../common/word_data.h"
#include "analyzer.h"

using namespace std;

/* IDEA CORNER:
 * Pentru fiecare cuvant din dictionar:
 *     Tratam, pe rand, fiecare cuvant din dictionar ca fiind "guess"
 *     Incrementam pattern-ul rezultat din joc
 *     La final calculam posibilitatile pt fiecare pattern
 *     Construim entropia lui "word" si o salvam intr-o structura
 * La final afisam toate rezultatele.
 *
 * Codarea pattern-urilor va fi de forma "ABCDE" (fiecare litera va fi o cifra din {0, 1, 2} si va fi
 * reprezentat printr-un numar covertit din baza 3 in baza 10
 * (Practic, pattern-ul "ABCDE" va avea asociat numarul:
 *      81 * A + 27 * B + 9 * C + 3 * D + E
 */

static const int N_PATTERNS = 243; // 3^5

void analyzer::run()
{
    cout << "Te rog asteapta..." << endl;

    vector<word_data> ent_cuvinte;
    for (const string& word : dictionary.vcuvinte)
    {
        int patterns[N_PATTERNS] = {0};
        int possible = 0;

        for (const string& guess : dictionary.vcuvinte)
        {
            int litere[26] = {0};
            int status[5] = {0}; 
            
            /* Va fi considerata urmatoarea codare:
             * status[i] = 0 => litera gri
             * status[i] = 1 => litera verde
             * status[i] = 2 => litera galbena 
             */

            // Pasul 1: Cream vector de frecventa cu numarul aparitiilor fiecarei litere
            for (const char& c : word)
                litere[c - 'A']++;

            // Pasul 2: Determinam literele verzi
            for (int i = 0; i < 5; i++)
            {
                if (guess[i] == word[i])
                {
                    status[i] = 1;
                    litere[guess[i] - 'A']--;
                }
            }
            
            // Pasul 3: Determinam literele galbene
            for (int i = 0; i < 5; i++)
            {
                if (status[i] == 0 && litere[guess[i] - 'A'] > 0)
                {
                    status[i] = 2;
                    litere[guess[i] - 'A']--;
                }
            }

            int cod_p = patternToInt(status);
            patterns[cod_p]++;
            possible++;
        }

        double entropy = 0.0;
        for (int pattern : patterns)
        {
            double p = 1.0 * pattern / possible;
            if (p == 0) continue;
            double v = p * log2(1.0 / p);
            entropy += v;
        }
        ent_cuvinte.emplace_back(word, entropy);
    }

    sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

    ofstream out("../entropy_list.txt");
    for (const word_data& i : ent_cuvinte)
    {
        out << i.word << " : " << i.entropy << "\n";
    }
    out.close();

    cout << "Rezultate salvate in entropy_list.txt" << endl;
}

#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include "analyzer.h"
#include "../common/word_data.h"
#include "../common/wordle.h"
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
            int* status = wordle::getPattern(word, guess);
            int cod_p = encodePattern(status);
            delete status;
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

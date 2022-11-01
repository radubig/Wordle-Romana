#include "Analyzer.h"
#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>

using namespace std;

/* IDEA CORNER:
 * Pentru fiecare "word" din dictionar:
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

static const int POSSIBILE = 11454;
static const int N_PATTERNS = 243;

void Analyzer::run()
{
    cout << "Running Analyzer, please wait..." << endl;

    vector<AData> ent_cuvinte;
    for(const string& word : dictionary.vcuvinte)
    {
        int pattern[N_PATTERNS] = {0};

        for(const string& guess : dictionary.vcuvinte)
        {
            int litere[30] = {0};
            int status[5] = {0}; /* Va fi considerata urmatoarea codare:
                * status[i] = 0 => litera gri
                * status[i] = 1 => litera verde
                * status[i] = 2 => litera galbena */

            for(const char& c : word)
                litere[c - 'A']++;

            //Logica litere noua
            //pass 1: determinare litere verzi
            for(int i=0; i<5; i++) if(guess[i] == word[i])
            {
                status[i] = 1;
                litere[guess[i] - 'A']--;
            }
            //pass 2: determinare litere galbene
            for(int i=0; i<5; i++) if(status[i] == 0 && litere[guess[i] - 'A'] > 0)
            {
                status[i] = 2;
                litere[guess[i] - 'A']--;
            }

            int cod_p = 81 * status[0] +
                        27 * status[1] +
                        9  * status[2] +
                        3  * status[3] +
                             status[4];
            pattern[cod_p]++;
        }

        //Sanity check
        int sum = 0;
        for(int i = 0; i < N_PATTERNS; i++)
            sum += pattern[i];
        if(sum != POSSIBILE)
            cout << "Sanity check FAIL! Sum = " << sum << "\n";

        double entropy = 0.0;
        for(int i = 0; i < N_PATTERNS; i++)
        {
            double p = 1.0 * pattern[i] / POSSIBILE;
            if(p==0) continue;
            double v = p * log2(1.0 / p);
            entropy += v;
        }
        ent_cuvinte.push_back(AData(word, entropy));
    }

    sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<AData>());

    ofstream out("entropy_list.txt");
    for(const AData& i : ent_cuvinte)
    {
        out << i.word << " : " << i.entropy << "\n";
    }
    out.close();

    cout<<"\nAnalysis completed.\n";
    cout<<"Results saved in entropy_list.txt"<<endl;
}

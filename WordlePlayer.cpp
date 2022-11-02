#include "WordlePlayer.h"
#include "Analyzer.h" //pentru AData
#include <iostream>
#include <cmath>

using namespace std;

/*TODO: Versiunea curenta de WordlePlayer este o clasa ce nu interactioneaza cu jocul.
 *De asemenea, clasa asta e momentan implementata haotic. To be refactored.
 */

void WordlePlayer::run()
{
    int counter = 1;
    int in_pattern;
    words_list = dictionary.vcuvinte;
    cout << "[Wordle Player]: Started \n";

    //Conform entropy_list.txt (2.11.2022) cuvantul cu cea mai mare entropie este:
    //TARIE (6.42526)
    string guess = "TARIE";

    cout << "[Wordle Player]: TARIE \n";
    cout << "Input pattern: ";
    cin >> in_pattern;
    this->update(guess, in_pattern);

    while(in_pattern != 151)
    {
        ++counter;
        guess = this->analyze();
        cout << "[Wordle Player]: " << guess << "\n";
        cout << "Input pattern: ";
        cin >> in_pattern;
        this->update(guess, in_pattern);
    }

    cout << "[Wordle Player]: Word guessed in " << counter << " attempts." << endl;
}

void WordlePlayer::update(const string &guessed_word, int word_pattern)
{
    std::vector<string> newlist;
    for(const string& word : words_list)
    {
        int litere[30] = {0};
        int status[5] = {0}; /* Va fi considerata urmatoarea codare:
                * status[i] = 0 => litera gri
                * status[i] = 1 => litera verde
                * status[i] = 2 => litera galbena */

        for(const char& c : guessed_word)
            litere[c - 'A']++;

        //Logica litere noua
        //pass 1: determinare litere verzi
        for(int i=0; i<5; i++) if(word[i] == guessed_word[i])
            {
                status[i] = 1;
                litere[word[i] - 'A']--;
            }
        //pass 2: determinare litere galbene
        for(int i=0; i<5; i++) if(status[i] == 0 && litere[word[i] - 'A'] > 0)
            {
                status[i] = 2;
                litere[word[i] - 'A']--;
            }

        int cod_p = 81 * status[0] +
                    27 * status[1] +
                    9  * status[2] +
                    3  * status[3] +
                    status[4];

        if(cod_p == word_pattern)
            newlist.push_back(word);
    }

    words_list = newlist;
}

string WordlePlayer::analyze()
{
    static const int N_PATTERNS = 243;
    vector<AData> ent_cuvinte;
    for(const string& word : words_list)
    {
        int pattern[N_PATTERNS] = {0};

        for(const string& guess : words_list)
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

        double entropy = 0.0;
        for(int i = 0; i < N_PATTERNS; i++)
        {
            double p = 1.0 * pattern[i] / words_list.size();
            if(p==0) continue;
            double v = p * log2(1.0 / p);
            entropy += v;
        }
        ent_cuvinte.push_back(AData(word, entropy));
    }

    string best_word;
    double mx = 0.0;
    for(const AData& i : ent_cuvinte)
    {
        if(i.entropy > mx)
        {
            mx = i.entropy;
            best_word = i.word;
        }
    }

    return best_word;
}

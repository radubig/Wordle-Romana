#include "WordlePlayer.h"
#include "Analyzer.h" //pentru AData
#include <iostream>
#include <cmath>
#include <fstream>

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

    while(in_pattern != 121)
    {
        ++counter;
        guess = this->analyze();
        if(words_list.size() <= 16)
            cout << "[Wordle Player]: Going For The Win\n";
        cout << "[Wordle Player]: " << guess << "\n";
        cout << "Input pattern: ";
        cin >> in_pattern;
        this->update(guess, in_pattern);
    }

    cout << "[Wordle Player]: Word guessed in " << counter << " attempts." << endl;
}

void WordlePlayer::update(const string &guessed_word, int word_pattern)
{
    int litere_guess[30] = {0};
    int status_guess[5];
    /* Va fi considerata urmatoarea codare:
    * status[i] = 0 => litera gri
    * status[i] = 1 => litera verde
    * status[i] = 2 => litera galbena */

    for(int i=4; i>=0; i--)
    {
        status_guess[i] = word_pattern % 3;
        if(status_guess[i] == 2) litere_guess[guessed_word[i] - 'A']++;
        word_pattern /= 3;
    }

    std::vector<string> newlist;
    for(const string& word : words_list)
    {
        bool goodWord = true;
        int litere[30] = {0};

        for(int i=0; i<5; i++)
        {
            if(status_guess[i] == 1) //Verificare litere verzi
            {
                if(word[i] != guessed_word[i]) goodWord = false;
            }
            else if(word[i] == guessed_word[i]) //Verificare ca literele neverzi sa nu fie pe aceeasi pozitie
                goodWord = false;
            else
                litere[word[i] - 'A']++;
        }

        if(goodWord)
        {
            for(int i=0; i<26; i++)
                if(litere[i] < litere_guess[i]) goodWord = false;
        }

        if(goodWord)
            newlist.push_back(word);
    }

    words_list = newlist;

    /*dump words_list
    for(const string& word : words_list)
        cout << word << "\n"; */
}

string WordlePlayer::analyze()
{
    static const int N_PATTERNS = 243;
    static const int POSSIBILE = 11454;
    string best_word;

    if(words_list.size() <= 16) //daca avem doar 4 biti de incertitudine atunci mergem for the win (4 e ales arbitrar)
        best_word = words_list[0];
    else
    {
        vector<AData> ent_cuvinte;
        for (const string &word: dictionary.vcuvinte) {
            int pattern[N_PATTERNS] = {0};

            for (const string &guess: words_list) {
                int litere[30] = {0};
                int status[5] = {0}; /* Va fi considerata urmatoarea codare:
                * status[i] = 0 => litera gri
                * status[i] = 1 => litera verde
                * status[i] = 2 => litera galbena */

                for (const char &c: word)
                    litere[c - 'A']++;

                //Logica litere noua
                //pass 1: determinare litere verzi
                for (int i = 0; i < 5; i++)
                    if (guess[i] == word[i]) {
                        status[i] = 1;
                        litere[guess[i] - 'A']--;
                    }
                //pass 2: determinare litere galbene
                for (int i = 0; i < 5; i++)
                    if (status[i] == 0 && litere[guess[i] - 'A'] > 0) {
                        status[i] = 2;
                        litere[guess[i] - 'A']--;
                    }

                int cod_p = 81 * status[0] +
                            27 * status[1] +
                            9 * status[2] +
                            3 * status[3] +
                            status[4];
                pattern[cod_p]++;
            }

            double entropy = 0.0;
            for (int i = 0; i < N_PATTERNS; i++) {
                double p = 1.0 * pattern[i] / words_list.size();
                if (p == 0) continue;
                double v = p * log2(1.0 / p);
                entropy += v;
            }
            ent_cuvinte.emplace_back(word, entropy);
        }

        double mx = 0.0;
        for (const AData &i: ent_cuvinte) {
            if (i.entropy > mx) {
                mx = i.entropy;
                best_word = i.word;
            }
        }

        /*dump entropy data in dump.txt
        ofstream out("dump.txt");
        for (const AData &i: ent_cuvinte)
            out << i.word << " : " << i.entropy << "\n";
        out.close();
        */
    }

    return best_word;
}

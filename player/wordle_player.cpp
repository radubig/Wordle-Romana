#include <algorithm>
#include <fstream>
#include <iostream>
#include "wordle_player.h"
#include "../common/entropy.h"
#include "../common/patterns.h"
using namespace std;

void wordle_player::run()
{
    int counter = 1;
    int in_pattern;
    words_list = dictionary.vcuvinte;

    // Conform entropy_list.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
    // TARIE (6.42526)
    string guess = "TARIE";

    cout << "Ghiceste: TARIE\n"
            "Introdu codul raspunsului: ";
    cin >> in_pattern;
    this->update(guess, in_pattern);

    while (in_pattern != GUESSED_PATTERN)
    {
        counter++;
        
        if (words_list.size() == 1)
        {
            cout << "Ghiceste: " << words_list[0] << "\n";
            cout << "Cuvant ghicit in " << counter << " incercari.\n" << endl;
            return;
        }
        
        guess = this->analyze();
        cout << "Ghiceste: " << guess << "\n"
                "Input pattern: ";
        cin >> in_pattern;
        this->update(guess, in_pattern);
    }

    if (counter == 1)
        cout << "Cuvant ghicit in 1 incercare.\n" << endl;
    else
        cout << "Cuvant ghicit in " << counter << " incercari.\n" << endl;
}

void wordle_player::update(const string &guessed_word, int word_pattern)
{
    int *status_guess = patterns::decode_pattern(word_pattern);
    int galbene_guess[26] = {0};

    for (int i = 0; i < 5; i++)
    {
        if (status_guess[i] == YELLOW) galbene_guess[guessed_word[i] - 'A']++;
    }

    std::vector<string> newlist;
    for (const string& word : words_list)
    {
        bool goodWord = true;
        int litere[26] = {0};

        for (int i = 0; i < 5; i++)
        {
            if (status_guess[i] == GREEN) //Verificare litere verzi
            {
                if (word[i] != guessed_word[i])
                {
                    goodWord = false;
                    break;
                }
            }
            else if (word[i] == guessed_word[i]) //Verificare ca literele neverzi sa nu fie pe aceeasi pozitie
            {
                goodWord = false;
                break;
            }
            else
            {
                litere[word[i] - 'A']++;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            if (litere[i] < galbene_guess[i])
            {
                goodWord = false;
                break;
            }    
        }

        if (goodWord) newlist.push_back(word);
    }
    
    words_list = newlist;

    cout << "Cuvinte posibile: ";
    for (const string& word : words_list)
        cout << word << " ";
    cout << endl;
}

string wordle_player::analyze()
{
    string best_word;

    vector<word_data> ent_cuvinte = entropy::calculate_entropy(dictionary.vcuvinte, words_list);
    sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

    best_word = ent_cuvinte[0].word;
    
    ofstream out("../entropy_dump.txt");
    for (const word_data& i : ent_cuvinte)
    {
        out << i.word << " : " << i.entropy << "\n";
    }
    out.close();

    return best_word;
}
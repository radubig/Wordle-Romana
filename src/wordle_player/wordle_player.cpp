#include <algorithm>
#include <fstream>
#include <iostream>
#include "wordle_player.h"
#include "../_common/entropy.h"
#include "../_common/patterns.h"
using namespace std;

void wordle_player::reset()
{
    words_list = dictionary.vcuvinte;    
}

string wordle_player::get_best_guess()
{
    if (words_list.size() == 1) return words_list[0];
    
    string best_word;

    vector<word_data> ent_cuvinte = entropy::calculate_entropy(dictionary.vcuvinte, words_list);
    sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

    best_word = ent_cuvinte[0].word;
    
    if (dump)
    {
        ofstream out("../entropy_dump.txt");
        for (const word_data& i : ent_cuvinte)
        {
            out << i.word << " : " << i.entropy << "\n";
        }
        out.close();
    }

    return best_word;
}

void wordle_player::apply_guess(const std::string &guessed_word, int pattern_code)
{
    int *status_guess = patterns::decode_pattern(pattern_code);
    int galbene_guess[26] = {0};
    int gri_guess[26] = {0};

    for (int i = 0; i < 5; i++)
    {
        if (status_guess[i] == YELLOW) galbene_guess[guessed_word[i] - 'A']++;
        else if (status_guess[i] == GREY) gri_guess[guessed_word[i] - 'A'] = 1;
    }

    std::vector<string> newlist;
    for (const string& word : words_list)
    {
        bool goodWord = true;
        int litere[26] = {0};

        for (int i = 0; i < 5; i++)
        {
            if (status_guess[i] == GREEN) // Verificare litere verzi
            {
                if (word[i] != guessed_word[i])
                {
                    goodWord = false;
                    break;
                }
            }
            else if (word[i] == guessed_word[i]) // Verificare ca literele neverzi sa nu fie pe aceeasi pozitie
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
            if (litere[i] < galbene_guess[i]) // Verificare litere galbene
            {
                goodWord = false;
                break;
            }

            if (gri_guess[i] == 1 && litere[i] > 0) // Verificare litere gri
            {
                goodWord = false;
                break;
            }
        }

        if (goodWord) newlist.push_back(word);
    }

    words_list = newlist;
}

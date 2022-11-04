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
    
    vector<word_data> ent_cuvinte = entropy::calculate_entropy(dictionary.vcuvinte, words_list);

    sort(ent_cuvinte.begin(), ent_cuvinte.end(), [this](const word_data& a, const word_data& b)
    {
        // Daca returnam true, atunci a va fi inainte de b (implementare operator >)
        
        if (a.entropy > b.entropy) return true;
        if (a.entropy < b.entropy) return false;

        bool a_in_word_list = count(words_list.begin(), words_list.end(), a.word);
        bool b_in_word_list = count(words_list.begin(), words_list.end(), b.word);
        
        if (a_in_word_list && !b_in_word_list) return true;
        if (b_in_word_list && !a_in_word_list) return false;
        
        return a.word < b.word;
    });

    if (dump)
    {
        ofstream out("entropy_dump.txt");
        for (const word_data& i : ent_cuvinte)
        {
            out << i.word << " : " << i.entropy << "\n";
        }
        out.close();
    }
    
    return ent_cuvinte[0].word;
}

bool check_guess(const std::string &guess, int* const& pattern, const std::string &word)
{
    int occ[26] = {0};
    bool max[26] = {false};

    for (int i = 0; i < 5; i++)
    {
        occ[word[i] - 'A']++;

        switch (pattern[i])
        {
            case GRAY:
                // Daca litera este gri atunci cuvantul contine atatea litere cat sunt colorate galben sau verde
                if (word[i] == guess[i]) return false;
                max[guess[i] - 'A'] = true;
                break;

            case GREEN:
                // Daca litera este verde atunci cuvantul are acea litera pe acea pozitie
                if (word[i] != guess[i]) return false;
                occ[guess[i] - 'A']--;
                break;

            case YELLOW:
                // Daca litera este galbena atunci cuvantul are acea litera, dar nu pe acea pozitie
                if (word[i] == guess[i]) return false;
                occ[guess[i] - 'A']--;
                break;
        }
    }

    // Verificam daca cuvantul are destule aparitii ale fiecarei litere pentru a satisface conditiile
    for (int i = 0; i < 26; ++i)
    {
        if (max[i])
        {
            if (occ[i] != 0) return false;
        }
        else
        {
            if (occ[i] < 0) return false;
        }
    }
    
    return true;
}

void wordle_player::apply_guess(const std::string &guessed_word, int pattern_code)
{
    int *status_guess = patterns::decode_pattern(pattern_code);
    
    words_list.erase
    (
        remove_if(words_list.begin(), words_list.end(), [guessed_word, status_guess](const string& word) 
        {
            return !check_guess(guessed_word, status_guess, word); 
        }),
        words_list.end()
    );
}

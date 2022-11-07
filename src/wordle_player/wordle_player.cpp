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
    if (number_of_guesses == 1)
        return second_guesses[_patterncodecache];

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
            case patterns::GRAY:
                // Daca litera este gri atunci cuvantul contine atatea litere cat sunt colorate galben sau verde
                if (word[i] == guess[i]) return false;
                max[guess[i] - 'A'] = true;
                break;

            case patterns::GREEN:
                // Daca litera este verde atunci cuvantul are acea litera pe acea pozitie
                if (word[i] != guess[i]) return false;
                occ[guess[i] - 'A']--;
                break;

            case patterns::YELLOW:
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

    //Done: Construct another vector and assign it to words_list. push_back() and assignment are way faster than linear search and removal!!!

    /*
    words_list.erase
    (
        remove_if(words_list.begin(), words_list.end(), [guessed_word, status_guess](const string& word) 
        {
            return !check_guess(guessed_word, status_guess, word); 
        }),
        words_list.end()
    );
     */

    vector<string> new_list;
    for(const string& word : words_list)
    {
        if(check_guess(guessed_word, status_guess, word))
            new_list.push_back(word);
    }
    words_list = new_list;

    number_of_guesses++;
    _patterncodecache = pattern_code; //TODO: maybe refactor?
}

void wordle_player::Load2ndGuessCache()
{
    ifstream in("2nd_guesses.txt");
    if(!in.is_open())
    {
        cerr << "Fatal: 2nd_guesses.txt not found!" << endl;
        throw;
    }
    while(!in.eof())
    {
        string word;
        in >> word;
        if(word.size() == 5)
            second_guesses.push_back(word);
    }
    in.close();
    if(second_guesses.size() != NUM_PATTERNS)
    {
        cerr << "Error: Second guesses cache vector size is not 243!" << endl;
        throw;
    }
}

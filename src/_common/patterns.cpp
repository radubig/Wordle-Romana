#include "patterns.h"
#include <cstring>

int pattern[5]{patterns::GRAY};

inline void clear_pattern()
{
    /*
    for (int i = 0; i < 5; i++)
    {
        pattern[i] = patterns::GRAY;
    }
     */
    memset(pattern, 0, sizeof(pattern));
}

int* patterns::get_pattern(const std::string &target, const std::string &guess)
{
    int litere[26] = {0};

    clear_pattern();

    /* Va fi considerata urmatoarea codare:
     * status[i] = 0 => litera gri
     * status[i] = 1 => litera verde
     * status[i] = 2 => litera galbena 
     */

    // Pasul 1: Cream vector de frecventa cu numarul aparitiilor fiecarei litere
    for (const char& c : target)
        litere[c - 'A']++;

    // Pasul 2: Determinam literele verzi
    for (int i = 0; i < 5; i++)
    {
        if (guess[i] == target[i])
        {
            pattern[i] = GREEN;
            // litere[guess[i] - 'A']--; // Conform precizarilor domnului profesor, folosim logica simpla de determinare a literelor galbene :(
        }
    }

    // Pasul 3: Determinam literele galbene
    for (int i = 0; i < 5; i++)
    {
        if (pattern[i] == GRAY && litere[guess[i] - 'A'] > 0)
        {
            pattern[i] = YELLOW;
            // litere[guess[i] - 'A']--; // Conform precizarilor domnului profesor, folosim logica simpla de determinare a literelor galbene :(
        }
    }
    
    return pattern;
}

int patterns::encode_pattern(const int* status) 
{
    return 81 * status[0] +
           27 * status[1] +
            9 * status[2] +
            3 * status[3] +
                status[4];
}

int* patterns::decode_pattern(int cod_p)
{
    clear_pattern();
    
    for (int i = 4; i >= 0; i--)
    {
        pattern[i] = cod_p % 3;
        cod_p /= 3;
    }
    
    return pattern;
}
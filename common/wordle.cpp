#include "wordle.h"

int* wordle::getPattern(const string& target, const string& guess)
{
    int litere[26] = {0};
    static int status[5] = {GRI};

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
            status[i] = VERDE;
            litere[guess[i] - 'A']--;
        }
    }

    // Pasul 3: Determinam literele galbene
    for (int i = 0; i < 5; i++)
    {
        if (status[i] == 0 && litere[guess[i] - 'A'] > 0)
        {
            status[i] = GALBEN;
            litere[guess[i] - 'A']--;
        }
    }
    
    return status;
}
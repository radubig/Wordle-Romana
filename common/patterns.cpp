#include "patterns.h"

int* patterns::get_pattern(const std::string &target, const std::string &guess)
{
    int litere[26] = {0};
    static int status[5] = {GRAY};

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
            status[i] = GREEN;
            litere[guess[i] - 'A']--;
        }
    }

    // Pasul 3: Determinam literele galbene
    for (int i = 0; i < 5; i++)
    {
        if (status[i] == 0 && litere[guess[i] - 'A'] > 0)
        {
            status[i] = YELLOW;
            litere[guess[i] - 'A']--;
        }
    }
    
    return status;
}

int patterns::encode_pattern(const int* status) 
{
    return 81 * status[0] + 27 * status[1] + 9 * status[2] + 3 * status[3] + status[4];
}

int* patterns::decode_pattern(int cod_p) 
{
    static int status[5] = {0};
    
    for (int i = 4; i >= 0; i--)
    {
        status[i] = cod_p % 3;
        cod_p /= 3;
    }
    
    return status;
}
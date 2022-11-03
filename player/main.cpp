#include <iostream>
#include "wordle_player.h"
using namespace std;

int main()
{
    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        wordle_player player(dict);
        player.run();
        
        return 0;
    }
    catch(...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

#include <iostream>
#include "wordle_game.h"
using namespace std;

int main()
{
    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        wordle_game game(dict);
        game.play();
        
        return 0;
    }
    catch(...)
    {
        cout << "A aparut o eroare." << std::endl;
        return -1;
    }
}

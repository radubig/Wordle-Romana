#include <iostream>
#include "wordle_game.h"

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
        std::cerr << "A aparut o eroare." << std::endl;
        return -1;
    }
}

#include "WordleGame.h"
#include <iostream>

int main()
{
    try
    {
        wordle_dict dict("cuvinte.txt", 11454);
        dict.init();

        WordleGame game(dict);
        game.play();
    }
    catch(...)
    {
        std::cerr << "An exception has occured!" << std::endl;
        return -1;
    }
    return 0;
}

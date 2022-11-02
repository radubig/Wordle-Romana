#include "WordleGame.h"
#include <iostream>

int main()
{
    try
    {
        WordleDict dict("cuvinte.txt", 11454);
        dict.init();

        WordleGame game(dict);
        game.play("CRETA");
    }
    catch(...)
    {
        std::cerr << "An exception has occured!" << std::endl;
        return -1;
    }
    return 0;
}

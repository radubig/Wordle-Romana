#include "WordlePlayer.h"
#include <iostream>

int main()
{
    try
    {
        WordleDict dict("cuvinte.txt", 11454);
        dict.init();

        WordlePlayer player(dict);
        player.run();
    }
    catch(...)
    {
        std::cerr << "An exception has occured!" << std::endl;
        return -1;
    }
    return 0;
}

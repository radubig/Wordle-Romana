#include <iostream>
#include "WordleGame.h"
using namespace std;

int main()
{
    try
    {
        WordleGame game("cuvinte.txt", 11454);
        game.init();
        game.play();
        game.clear();
        return 0;
    }
    catch (...)
    {
        cout << "A aparut o eroare.";
        return 1;
    }
}

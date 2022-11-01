#include <iostream>
#include "WordleGame.h"
using namespace std;

int main()
{
    try
    {
        WordleDict dict("cuvinte.txt", 11454);
        dict.init();
        WordleGame game(dict);
        game.play("ABRAS");

        dict.clear();
        return 0;
    }
    catch (...)
    {
        cout << "A aparut o eroare.";
        return 1;
    }
}

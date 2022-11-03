#include <iostream>

#include "../game/WordleGame.h"
#include "analyzer.h"

using namespace std;

int main()
{
    //Timp de rulare cod in Modul Debug: ~15 secunde
    //Timp de rulare cod in Modul Release: ~2 secunde

    try
    {
        wordle_dict dict("./cuvinte.txt");
        dict.init();

        analyzer analyzer(dict);
        analyzer.run();

        dict.clear();
        return 0;
    }
    catch (...)
    {
        cout << "A aparut o eroare.";
        return 1;
    }
}

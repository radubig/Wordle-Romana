#include <iostream>
#include "WordleGame.h"
#include "Analyzer.h"
using namespace std;

int main()
{
    //Timp de rulare cod in Modul Debug: ~15 secunde
    //Timp de rulare cod in Modul Release: ~2 secunde

    try
    {
        WordleDict dict("cuvinte.txt", 11454);
        dict.init();

        Analyzer analyzer(dict);
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

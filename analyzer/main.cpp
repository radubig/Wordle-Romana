#include <iostream>
#include "analyzer.h"

using namespace std;

int main()
{
    //Timp de rulare cod in Modul Debug: ~15 secunde
    //Timp de rulare cod in Modul Release: ~2 secunde

    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        analyzer analyzer(dict);
        analyzer.run();

        return 0;
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

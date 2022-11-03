#include <cmath>
#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include "analyzer.h"
#include "../common/entropy.h"
#include "../common/patterns.h"
using namespace std;

int main()
{
    //Timp de rulare cod in Modul Debug: ~15 secunde
    //Timp de rulare cod in Modul Release: ~2 secunde

    try
    {
        word_dict dict("../cuvinte.txt");
        dict.init();

        cout << "Te rog asteapta..." << endl;

        vector<word_data> ent_cuvinte = entropy::calculate_entropy(dict.vcuvinte, dict.vcuvinte);
        sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

        ofstream out("../first_guess_entropy.txt");
        for (const word_data& i : ent_cuvinte)
        {
            out << i.word << " : " << i.entropy << "\n";
        }
        out.close();

        cout << "Rezultate salvate in entropy_list.txt" << endl;

        return 0;
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }
}

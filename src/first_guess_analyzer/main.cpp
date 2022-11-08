#include <fstream>
#include <functional>
#include <iostream>
#include <vector>
#include "../_common/entropy.h"
#include "../_common/paths.h"
#include "../_common/word_dict.h"
using namespace std;

int main()
{
    try
    {
        word_dict dict(WORD_DICTIONARY_FILE_PATH);
        dict.init();

        cout << "Te rog asteapta..." << endl;

        vector<word_data> ent_cuvinte = entropy::calculate_entropy(dict.vcuvinte, dict.vcuvinte);
        sort(ent_cuvinte.begin(), ent_cuvinte.end(), greater<>());

        ofstream out(FIRST_GUESS_FILE_PATH);
        for (const word_data& i : ent_cuvinte)
        {
            out << i.word << " : " << i.entropy << "\n";
        }
        out.close();

        cout << "Rezultate salvate in " << FIRST_GUESS_FILE_PATH << endl;

        return 0;
    }
    catch (const runtime_error& e)
    {
        cerr << "A aparut o eroare." << endl;
        cerr << e.what();
        return -1;
    }
    catch (...)
    {
        cerr << "A aparut o eroare neasteptata." << endl;
        return -1;
    }
}

#include <fstream>
#include <iostream>
#include "word_dict.h"

using namespace std;

void word_dict::init()
{
    ifstream in(file);
    if (!in.is_open())
    {
        cout << "Fisierul " << file << " nu a putut fi deschis!" << endl;
        throw runtime_error("");
    }
    while (!in.eof())
    {
        string s;
        in >> s;
        if(s.size() != 5)
        {
            cout << "Cuvantul " << s << " nu are 5 litere!" << endl;
            continue;
        }
        cuvinte.insert(s);
        vcuvinte.push_back(s);
    }
    in.close();
    cout << "Dictionar incarcat." << endl;
}

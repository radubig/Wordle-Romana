#include <fstream>
#include <iostream>
#include "word_dict.h"

using namespace std;

void word_dict::init()
{
    ifstream in(file);
    if (!in.is_open())
        throw runtime_error("Nu s-a putut deschide dictionarul de cuvinte.");
    while (!in.eof())
    {
        string s;
        in >> s;
        if (s.size() != 5)
            throw runtime_error("Cuvantul " + s + " nu are 5 litere!");
        cuvinte.insert(s);
        vcuvinte.push_back(s);
    }
    in.close();
}

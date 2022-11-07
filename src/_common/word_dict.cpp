#include <fstream>
#include <iostream>
#include "word_dict.h"

using namespace std;

void word_dict::init()
{
    ifstream in(file);
    if (!in.is_open())
        throw runtime_error("");
    while (!in.eof())
    {
        string s;
        in >> s;
        if (s.size() != 5)
            throw;
        cuvinte.insert(s);
        vcuvinte.push_back(s);
    }
    in.close();
}

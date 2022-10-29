#include "WordleDict.h"
#include <iostream>
#include <fstream>
using namespace std;

void WordleDict::init() {
    cuvinte.reserve(dictSize);
    vcuvinte.reserve(dictSize);

    ifstream in(file);
    if(!in.is_open())
    {
        cout << "Fisierul " << file << " nu a putut fi deschis!" << endl;
        throw NULL;
    }
    while(!in.eof())
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

void WordleDict::clear() {
    cuvinte.clear();
    vcuvinte.clear();
    file.clear();
}

#include <fstream>
#include <iostream>
#include "wordle_dict.h"
using namespace std;

void wordle_dict::init() {
    ifstream in(file);
    if(!in.is_open())
    {
        cout << "Fisierul " << file << " nu a putut fi deschis!" << endl;
        throw runtime_error("");
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

void wordle_dict::clear() {
    cuvinte.clear();
    vcuvinte.clear();
    file.clear();
}

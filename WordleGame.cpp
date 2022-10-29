#include "WordleGame.h"
#include <cstring>
#include <random>
#include <set>
using namespace std;

void WordleGame::play(const string& forceCuv)
{
    string word;
    string guess;
    set<char> litere;

    srand(time(NULL));
    int indexCuv = rand() % dictionary.cuvinte.size();
    word = dictionary.vcuvinte[indexCuv];
    
    if (!forceCuv.empty()) word = forceCuv;
    
    for(const char& c : word)
        litere.insert(c);

    cout << "Wordle in romana: incearca sa ghicesti un cuvant de 5 litere!\n"
               //"Introdu cuvinte de cate 5 litere pana cand ghicesti cuvantul!\n"
                 "Vei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\n"
                 "Esti pregatit? Tasteaza un cuvant de 5 litere:" << endl;
    do
    {
        cin >> guess;

        if(guess.size() != 5)
        {
            cout<<"Cuvantul introdus nu are 5 litere! Introdu alt cuvant:"<<endl;
            continue;
        }

        bool isValid = true;
        for(char& c : guess)
        {
            if(c >= 'a' && c <= 'z')
                c -= 32;
            else if(!(c >= 'A' && c <= 'Z'))
                isValid = false;
        }
        if(!isValid)
        {
            cout<<"Cuvantul introdus contine si alte caractere in afara de litere!\nIntrodu alt cuvant:"<<endl;
            continue;
        }

        if(dictionary.cuvinte.find(guess) == dictionary.cuvinte.end())
        {
            cout<<"Cuvantul introdus nu face parte din dictionar! Introdu alt cuvant:"<<endl;
            continue;
        }

        //Aici este impementata logica de determinare a literelor corecte
        for(int i=0; i<5; i++)
        {
            if(guess[i] == word[i])
                cout<<guess[i]<<": Corect!\n";
            else if(litere.find(guess[i]) != litere.end())
                cout<<guess[i]<<": Alta pozitie!\n";
            else
                cout<<guess[i]<<": Nu exista!\n";
        }
        cout<<endl;

    }while(guess != word);

    cout<< "FELICITARI! Ai ghicit cuvantul!\n" <<endl;
}

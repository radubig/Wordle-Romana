#include "WordleGame.h"
#include <cstring>
#include <random>

using namespace std;

void WordleGame::play(const string& forceCuv)
{
    string word;
    string guess;

    srand(time(NULL));
    int indexCuv = rand() % dictionary.cuvinte.size();
    word = dictionary.vcuvinte[indexCuv];
    
    if (!forceCuv.empty()) word = forceCuv;

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

        int litere[30] = {0};
        int status[5] = {0}; /* Va fi considerata urmatoarea codare:
                * status[i] = 0 => litera gri
                * status[i] = 1 => litera verde
                * status[i] = 2 => litera galbena */

        for(const char& c : word)
            litere[c - 'A']++;

        //Logica litere noua
        //pass 1: determinare litere verzi
        for(int i=0; i<5; i++) if(guess[i] == word[i])
        {
            status[i] = 1;
            litere[guess[i] - 'A']--;
        }
        //pass 2: determinare litere galbene
        for(int i=0; i<5; i++) if(status[i] == 0 && litere[guess[i] - 'A'] > 0)
        {
            status[i] = 2;
            litere[guess[i] - 'A']--;
        }

        //TODO: De colorat literele corespunzator in consola!
        for(int i=0; i<5; i++)
        {
            if(status[i] == 1)
                cout<<guess[i]<<": Corect!\n";
            else if(status[i] == 2)
                cout<<guess[i]<<": Alta pozitie!\n";
            else //status[i] == 0
                cout<<guess[i]<<": Nu exista!\n";
        }
        int cod_p = 81 * status[0] +
                    27 * status[1] +
                    9  * status[2] +
                    3  * status[3] +
                    status[4];
        cout<<"Cod pattern: " << cod_p;
        cout<<endl;

    }while(guess != word);

    cout<< "FELICITARI! Ai ghicit cuvantul!\n" <<endl;
}

#include "WordleGame.h"
#include <cstring>
#include <random>
#include <set>

void WordleGame::init()
{
    std::ifstream in(file);
    if(!in.is_open())
    {
        std::cout << file << " could not be opened!" << std::endl;
        return;
    }
    while(!in.eof())
    {
        string s;
        in >> s;
        if(s.size() != 5)
        {
            std::cout << "Cuvantul " << s << " nu are 5 litere!" << std::endl;
            continue;
        }
        cuvinte.insert(s);
        vcuvinte.push_back(s);
    }
    in.close();
    std::cout << "Dictionar incarcat." <<std::endl;
}

void WordleGame::play()
{
    if(cuvinte.empty() || vcuvinte.empty())
    {
        std::cout << "EROARE: Dictionarul este gol sau nu a fost initializat." <<std::endl;
    }

    string guess;
    std::set<char> litere;

    srand(time(NULL));
    int indexCuv = rand() % cuvinte.size();
    word = vcuvinte[indexCuv];
    for(const char& c : word)
        litere.insert(c);

    std::cout << "Wordle in romana: incearca sa ghicesti un cuvant de 5 litere!\n"
               //"Introdu cuvinte de cate 5 litere pana cand ghicesti cuvantul!\n"
                 "Vei primi la fiecare incercare indicatii despre ce litere fac parte din cuvant.\n\n"
                 "Esti pregatit? Tasteaza un cuvant de 5 litere:" << std::endl;
    do
    {
        std::cin >> guess;

        if(guess.size() != 5)
        {
            std::cout<<"Cuvantul introdus nu are 5 litere! Introdu alt cuvant:"<<std::endl;
            continue;
        }

        if(cuvinte.find(guess) == cuvinte.end())
        {
            std::cout<<"Cuvantul introdus nu face parte din dictionar! Introdu alt cuvant:"<<std::endl;
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
            std::cout<<"Cuvantul introdus contine si alte caractere in afara de litere!\nIntrodu alt cuvant:"<<std::endl;
            continue;
        }

        //Aici este impementata logica de determinare a literelor corecte
        for(int i=0; i<5; i++)
        {
            if(guess[i] == word[i])
                std::cout<<guess[i]<<": Corect!\n";
            else if(litere.find(guess[i]) != litere.end())
                std::cout<<guess[i]<<": Alta pozitie!\n";
            else
                std::cout<<guess[i]<<": Nu exista!\n";
        }
        std::cout<<std::endl;

    }while(guess != word);

    std::cout<< "FELICITARI! Ai ghicit cuvantul!\n" <<std::endl;
}

void WordleGame::clear()
{
    cuvinte.clear();
    vcuvinte.clear();
    file.clear();
}

void WordleGame::hint(uint32_t sz)
{
    cuvinte.reserve(sz);
    vcuvinte.reserve(sz);
}

void WordleGame::setfile(const string &src)
{
    file = src;
}


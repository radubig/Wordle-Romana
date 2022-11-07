#include <iostream>
#include "wordle_player.h"
#include "../_common/patterns.h"
#include "../_common/ipc.h"

using namespace std;
namespace bp = boost::process;

static void StandardPlay();
static void AutoPlay(vector<string>&, bp::ipstream&, bp::opstream&);

int main(int argc, char** argv)
{
    try
    {
        if(argc < 2)
        {
            StandardPlay();
        }
        else
        {
            //Command line args:
            //Player: ./WordlePlayer -auto
            //calls: ./WordleGame -auto
            vector<string> data;

            bp::ipstream bufin;
            bp::opstream bufout;
            bp::child Child ("WordleGame", "-auto", bp::std_out > bufin, bp::std_in < bufout);
            AutoPlay(data, bufin, bufout);

            Child.wait();
            if(Child.exit_code() != 0)
                cerr << "Child gave up on life" << endl;

            cout << "Cuvinte ghicite:\n";
            for(const string& i : data)
                cout << i << "\n";
            cout << "Cuvantul " << *(data.rbegin()) << " a fost ghicit in " << data.size() << " incercari." << endl;
        }
    }
    catch (...)
    {
        cerr << "A aparut o eroare." << endl;
        return -1;
    }

    return 0;
}

inline static void StandardPlay()
{
    word_dict dict("cuvinte.txt");
    dict.init();

    wordle_player player(dict);
    //player.reset();

    int guesses = 1;
    int in_pattern;

    // Conform first_guess_entropy.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
    // TAREI (6.41381)
    string guess = FIRST_GUESS;

    cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
    cin >> in_pattern;
    player.apply_guess(guess, in_pattern);
    cout << "Cuvinte posibile: ";
    for (const string& word : player.words_list) cout << word << " ";
    cout << endl;

    while (in_pattern != GUESSED_PATTERN)
    {
        guesses++;

        if (player.words_list.size() == 1)
        {
            cout << "Ghiceste: " << player.words_list[0] << "\n";
            cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
            return;
        }

        guess = player.get_best_guess();
        cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
        cin >> in_pattern;
        player.apply_guess(guess, in_pattern);
        cout << "Cuvinte posibile: ";
        for (const string& word : player.words_list) cout << word << " ";
        cout << endl;
    }

    if (guesses == 1)
        cout << "Cuvant ghicit in 1 incercare.\n" << endl;
    else
        cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
}

inline static void AutoPlay(vector<string>& ans, bp::ipstream& bufin, bp::opstream& bufout)
{
    word_dict dict("cuvinte.txt");
    dict.init();

    wordle_player player(dict);
    //player.reset();

    int guesses = 1;
    int in_pattern;

    // Conform first_guess_entropy.txt (03.11.2022) cuvantul cu cea mai mare entropie este:
    // TAREI (6.41381)
    string guess = FIRST_GUESS;

    bufout << guess << endl;
    ans.push_back(guess);
    bufin >> in_pattern;

    player.apply_guess(guess, in_pattern);

    while (in_pattern != GUESSED_PATTERN)
    {
        guesses++;

        if (player.words_list.size() == 1)
        {
            bufout << player.words_list[0] << endl;
            ans.push_back(player.words_list[0]);
            return;
        }

        guess = player.get_best_guess();
        bufout << guess << endl;
        ans.push_back(guess);

        bufin >> in_pattern;
        player.apply_guess(guess, in_pattern);
    }

}

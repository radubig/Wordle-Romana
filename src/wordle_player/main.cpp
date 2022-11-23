#include <boost/process.hpp>
#include <iostream>
#include "wordle_player.h"
#include "../_common/paths.h"
#include "../_common/patterns.h"

using namespace std;
namespace bp = boost::process;

static void StandardPlay();
static void AutoPlay(bp::ipstream&, bp::opstream&, int);

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
            //Player: ./WordlePlayer -auto n
            //calls: ./WordleGame -auto n
            if(strcmp(argv[1], "-auto") != 0)
            {
                cout << "Usage: WordlePlayer [-auto [n]]\n"
                        "-auto: enables autoplay (requires WordleGame)\n"
                        "n: the number of iterations of Autoplay\n";
                return 0;
            }

            string s_n = "1";
            int n = 1;
            if(argc >= 3)
            {
                s_n = argv[2];
                n = atoi(argv[2]);
            }

            bp::ipstream bufin;
            bp::opstream bufout;
            bp::child Child ("WordleGame", bp::args({"-auto", s_n}), bp::std_out > bufin, bp::std_in < bufout);
            AutoPlay(bufin, bufout, n);

            Child.wait();
            if (Child.exit_code() != 0)
                cerr << "A aparut o eroare in subprocesul WorldeGame." << endl;

        }
    }
    catch (const runtime_error& e)
    {
        cerr << "A aparut o eroare." << endl;
        cerr << e.what() << endl;
        return -1;
    }
    catch (...)
    {
        cerr << "A aparut o eroare neasteptata." << endl;
        return -1;
    }
    
    return 0;
}

inline static void StandardPlay()
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    wordle_player player(dict);

    int guesses = 1;
    int in_pattern;

    string guess = FIRST_GUESS;

    cout << "Ghiceste: " << guess << "\nIntrodu codul raspunsului: ";
    cin >> in_pattern;
    player.apply_guess(guess, in_pattern);

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
    }

    if (guesses == 1)
        cout << "Cuvant ghicit in 1 incercare.\n" << endl;
    else
        cout << "Cuvant ghicit in " << guesses << " incercari.\n" << endl;
}

inline static void AutoPlay(bp::ipstream& bufin, bp::opstream& bufout, int n)
{
    word_dict dict(WORD_DICTIONARY_FILE_PATH);
    dict.init();

    wordle_player player(dict);

    for(int i=1; i<=n; i++)
    {
        player.reset();
        vector<string> ans;
        int in_pattern;

        string guess = FIRST_GUESS;

        bufout << guess << endl;
        ans.push_back(guess);
        bufin >> in_pattern;

        player.apply_guess(guess, in_pattern);

        while (in_pattern != GUESSED_PATTERN) {
            if (player.words_list.size() == 1) {
                bufout << player.words_list[0] << endl;
                bufin >> in_pattern;
                ans.push_back(player.words_list[0]);
                break;
            }

            guess = player.get_best_guess();
            bufout << guess << endl;
            ans.push_back(guess);

            bufin >> in_pattern;
            player.apply_guess(guess, in_pattern);
        }

        cout << "Cuvinte ghicite:\n";
        for (const string& s : ans)
            cout << s << "\n";
        cout << "Cuvantul " << *(ans.rbegin()) << " a fost ghicit in " << ans.size() << " incercari.\n" << endl;
    }

}

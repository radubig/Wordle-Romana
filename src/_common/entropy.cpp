#include <cmath>
#include "entropy.h"
#include "patterns.h"
using namespace std;

vector<word_data> entropies;

const vector<word_data>& entropy::calculate_entropy(const vector<string> &dictionar, const vector<string> &cuvinteRamase)
{
    entropies.clear();
    
    for (const string& guess : dictionar)
    {
        int patterns[NUM_PATTERNS] = {0};

        for (const string& word : cuvinteRamase)
        {
            int* status = patterns::get_pattern(word, guess);
            int cod_p = patterns::encode_pattern(status);
            patterns[cod_p]++;
        }

        double entropy = 0.0;
        for (int pattern : patterns)
        {
            double p = 1.0 * pattern / cuvinteRamase.size(); // NOLINT(cppcoreguidelines-narrowing-conversions)
            if (p == 0) continue;
            double v = p * log2(1.0 / p);
            entropy += v;
        }

        entropies.emplace_back(guess, entropy);
    }
    
    return entropies;
}
#include <cmath>
#include "entropy.h"
#include "patterns.h"
using namespace std;

vector<word_data> entropies;

void clear_entropy()
{
    entropies.clear();
}

vector<word_data> const& entropy::calculate_entropy(const vector<string> &dictionar, const vector<string> &cuvinteRamase)
{
    clear_entropy();
    
    for (const string& word : dictionar)
    {
        int patterns[N_PATTERNS] = {0};

        for (const string& guess : cuvinteRamase)
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

        entropies.emplace_back(word, entropy);
    }
    
    return entropies;
}
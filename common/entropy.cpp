#include <cmath>
#include "entropy.h"
#include "patterns.h"
using namespace std;

vector<word_data>* entropy::calculate_entropy(const vector<string> &cuvinte)
{
    static vector<word_data> ent_cuvinte;
    
    for (const string& word : cuvinte)
    {
        int patterns[N_PATTERNS] = {0};

        for (const string& guess : cuvinte)
        {
            int* status = patterns::get_pattern(word, guess);
            int cod_p = patterns::encode_pattern(status);
            delete status;
            patterns[cod_p]++;
        }

        double entropy = 0.0;
        for (int pattern : patterns)
        {
            double p = 1.0 * pattern / cuvinte.size(); // NOLINT(cppcoreguidelines-narrowing-conversions)
            if (p == 0) continue;
            double v = p * log2(1.0 / p);
            entropy += v;
        }
        
        ent_cuvinte.emplace_back(word, entropy);
    }
    
    return &ent_cuvinte;
}
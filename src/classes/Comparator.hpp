#include <iostream>
#include <vector>
#include <algorithm>
#include "Document.hpp"

using namespace std;

#define BANDS 25
#define ROWS 4

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(vector<Document *> V);

    vector<vector<double>> get_jaccard_similarity();

    vector<vector<double>> get_minhash_similarity();

    vector<vector<double>> get_lsh_similarity();

private:
    vector<Document *> docs;

    vector<int> generate_random_coefficients();

    float threshold;

    vector<unsigned> get_bands(vector<unsigned> &sig);
};

#endif

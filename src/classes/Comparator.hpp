#include <iostream>
#include <vector>
#include <algorithm>
#include "Document.hpp"

using namespace std;

#define DEFAULT_HASH_FUNCTIONS 50
#define DEFAULT_BANDS 25
#define DEFAULT_ROWS 2

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(vector<Document *> V);

    Comparator(vector<Document *> V, unsigned hf, unsigned ba, unsigned ro);

    void set_hash_functions(unsigned n);

    void set_bands_rows(unsigned b, unsigned r);

    vector<vector<double>> get_jaccard_similarity();

    vector<vector<double>> get_hashed_jaccard_similarity();

    vector<vector<double>> get_minhash_similarity();

    vector<vector<double>> get_lsh_similarity();

    vector<vector<double>> get_advanced_lsh_similarity();

private:
    unsigned bands;

    unsigned rows;

    unsigned hash_functions;

    float threshold;

    vector<Document *> docs;

    int get_levenshtein_distance(const string &s1, const string &s2);

    vector<unsigned> get_bands(vector<unsigned> &sig);

    vector<int> generate_random_coefficients();

};

#endif

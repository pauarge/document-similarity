#include <iostream>
#include <vector>
#include <algorithm>
#include "Document.hpp"

using namespace std;

#define DEFAULT_HASH_FUNCTIONS 50
#define DEFAULT_BANDS 25
#define DEFAULT_ROWS 4

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(vector<Document *> V);

    vector<vector<double>> get_jaccard_similarity();

    vector<vector<double>> get_minhash_similarity();

    vector<vector<double>> get_lsh_similarity();

    void setHashFunctions(unsigned n);

    void setBandsRows(unsigned b, unsigned r);

    vector<vector<double>> get_lshAdvanced_similarity();

private:
    vector<Document *> docs;

    vector<int> generate_random_coefficients();

    float threshold;

    unsigned BANDS;

    unsigned ROWS;

    unsigned HASH_FUNCTIONS;

    vector<unsigned> get_bands(vector<unsigned> &sig);

    int get_levenshtein_distance(const string &s1, const string &s2);

};

#endif

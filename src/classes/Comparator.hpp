#include <iostream>
#include <vector>
#include "Document.hpp"

using namespace std;

#define BANDS 250
#define ROWS 4

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(Document *doc1, Document *doc2);

    double get_jaccard_similarity();

    double get_minhash_similarity();

    double get_lsh_similarity();

private:
    Document *doc1;
    Document *doc2;

    float threshold;

    vector<int> generate_random_coefficients();

    vector<unsigned> get_bands(vector<unsigned> &sig);

};

#endif

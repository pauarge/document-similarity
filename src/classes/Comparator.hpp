#include <iostream>
#include <vector>
#include "Document.hpp"

using namespace std;

#define KSHINGLES 5
#define HASH_FUNCTIONS 100

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(Document *doc1, Document *doc2);

    double get_jaccard_similarity();

    double get_minhash_similarity();

private:
    Document *doc1;
    Document *doc2;

    vector<int> generate_random_coefficients();

    unsigned long fast_hash(int c1, int c2, unsigned long val);

};

#endif

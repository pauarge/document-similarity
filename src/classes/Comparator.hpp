#include <iostream>
#include <vector>
#include "Document.hpp"

using namespace std;

#ifndef DOCUMENT_SIMILARITY_COMPARATOR_HPP
#define DOCUMENT_SIMILARITY_COMPARATOR_HPP


class Comparator {

public:
    Comparator(Document *doc1, Document *doc2);
    Comparator(vector<Document*> V);

    double get_jaccard_similarity();
    vector< vector<double> > get_multi_jaccard_similarity();

    double get_minhash_similarity();
    vector< vector<double> > get_multi_minhash_similarity();

    double get_lsh_similarity();
    vector< vector<double> > get_multi_lsh_similarity();

private:
    Document *doc1;
    Document *doc2;

    vector<Document*> Docs;

    vector<int> generate_random_coefficients();
};

#endif

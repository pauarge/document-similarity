#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>
#include "Experiments.hpp"

using namespace std;

#define TEST_DOCS 20
#define KSHINGLES 9


#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

// TODO: Prevent crash with documents of length < k

public:
    bool valid;
    string data;
    string path;

    Document(bool b, string d);

    Document(std::string path);

    vector<unsigned> get_signature(vector<int> &c1, vector<int> &c2);

    set<unsigned> get_shingles(unsigned k) const;

    vector<Document *> get_permutations(int k) const;

    std::string get_permutation() const;

private:
    unsigned fast_hash(int c1, int c2, unsigned val);

};


#endif

#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>

using namespace std;

#define TEST_DOCS 0
#define KSHINGLES 9


#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

public:
    bool valid;
    string data;
    string path;

    Document(bool b, string d);

    Document(std::string path);

    vector<unsigned> get_signature(vector<int> &c1, vector<int> &c2, unsigned HASH_FUNCTIONS);

    set<unsigned> get_shingles(unsigned k) const;

    vector<Document *> get_permutations(int k) const;

    std::string get_permutation() const;

    unsigned fast_hash(int c1, int c2, unsigned val);

};


#endif

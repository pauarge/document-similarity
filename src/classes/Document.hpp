#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <cmath>
#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>

using namespace std;

#define TEST_DOCS 0
#define DEFAULT_KSHINGLES 9


#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

public:
    bool valid;
    unsigned kshingles;
    string data;
    string path;

    Document(bool b, string d, unsigned shingles);

    Document(bool b, string d);

    Document(string path, unsigned shingles);

    Document(string path);

    string get_permutation() const;

    vector<unsigned> get_signature(vector<int> &c1, vector<int> &c2, unsigned HASH_FUNCTIONS);

    vector<Document *> get_permutations(int k) const;

    set<string> get_shingles(unsigned k) const;

    set<unsigned> get_hashed_shingles(unsigned k) const;

private:
    unsigned fast_hash(int c1, int c2, unsigned val);

};

#endif

#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/crc.hpp>
#include <boost/functional/hash.hpp>

using namespace std;

#define KSHINGLES 9
#define HASH_FUNCTIONS 1000
#define BANDS 125
#define ROWS 8

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

    set<string> get_shingles(unsigned k) const;

    set<unsigned> get_hashed_shingles(unsigned k) const;

    std::vector<std::string> get_permutations(int k) const;

    std::string get_permutation() const;

private:
    unsigned fast_hash(int c1, int c2, unsigned val);

};


#endif

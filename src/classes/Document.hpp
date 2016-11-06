#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>
#include <boost/crc.hpp>

using namespace std;

#define KSHINGLES 9
#define HASH_FUNCTIONS 1000
#define BANDS 125
#define ROWS 8
#define THRESHOLD pow((1/BANDS),(1/ROWS))

#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

// TODO: Prevent crash with documents of length < k

public:
    bool valid;
    string data;
    string path;

    Document(std::string path);

    vector<unsigned> get_signature(vector<int> &c1, vector<int> &c2);

    set<string> get_shingles(unsigned k) const;

    set<unsigned> get_hashed_shingles(unsigned k) const;

private:
    unsigned fast_hash(int c1, int c2, unsigned val);

};


#endif

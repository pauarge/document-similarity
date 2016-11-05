#include <set>
#include <vector>
#include <iostream>
#include <fstream>
#include <boost/crc.hpp>

using namespace std;

#define KSHINGLES 9
#define HASH_FUNCTIONS 100

#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

// TODO: Prevent crash with documents of length < k

public:
    bool valid;
    string data;
    string path;

    Document(std::string path);

    vector<unsigned long> get_signature(vector<int> &c1, vector<int> &c2);

    set<string> get_shingles(unsigned k) const;

    set<unsigned long> get_hashed_shingles(unsigned k) const;

private:
    unsigned long fast_hash(int c1, int c2, unsigned long val);

};


#endif

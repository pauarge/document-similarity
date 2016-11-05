#include <set>
#include <iostream>
#include <fstream>
#include <boost/crc.hpp>

using namespace std;

#ifndef DOCUMENT_SIMILARITY_DOCUMENT_HPP
#define DOCUMENT_SIMILARITY_DOCUMENT_HPP


class Document {

public:
    bool valid;
    string data;
    string path;

    Document(std::string path);

    set<string> get_shingles(unsigned k) const;

    set<unsigned long> get_hashed_shingles(unsigned k) const;

};


#endif

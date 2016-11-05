#include "Document.hpp"


Document::Document(string path) {
    this->path = path;

    ifstream docfile;
    docfile.open(this->path);

    if (docfile.is_open()) {
        this->valid = true;

        docfile.seekg(0, ios::end);
        this->data.reserve(docfile.tellg());
        docfile.seekg(0, ios::beg);
        this->data.assign((istreambuf_iterator<char>(docfile)), istreambuf_iterator<char>());

        docfile.close();
    } else {
        this->valid = false;
    }
}


vector<unsigned long> Document::get_signature(vector<int> &c1, vector<int> &c2){
    set<unsigned long> shingles = this->get_hashed_shingles(KSHINGLES);
    vector<unsigned long> sig(HASH_FUNCTIONS);
    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        sig[i] = ULONG_MAX;
        for (unsigned long shingle : shingles) {
            sig[i] = min(sig[i], fast_hash(c1[i], c2[i], shingle));
        }
    }
    return sig;
}


set<string> Document::get_shingles(unsigned k) const {
    set<string> res;
    for (unsigned long i = 0; i <= this->data.length() - k; i++) {
        string temp = this->data.substr(i, k);
        res.insert(temp);
    }
    return res;
}

set<unsigned long> Document::get_hashed_shingles(unsigned k) const {
    set<unsigned long> res;
    for (unsigned long i = 0; i <= this->data.length() - k; i++) {
        string temp = this->data.substr(i, k);
        boost::crc_32_type h;
        h.process_bytes(temp.data(), temp.length());
        res.insert(h.checksum());
    }
    return res;
}

/**
 * Arbitrary hash function that generates a value from two random coefficients and an input.
 *
 * @param c1
 * @param c2
 * @param val
 * @return
 */
unsigned long Document::fast_hash(int c1, int c2, unsigned long val) {
    return (c1 * val + c2) % ULONG_MAX;
}
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


set<string> Document::get_shingles(unsigned k) const {
    set<string> res;
    for (unsigned long i = 0; i <= this->data.length() - k; i++) {
        string temp = this->data.substr(i, k);
        res.insert(temp);
    }
    return res;
}

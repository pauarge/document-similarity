#include <iterator>
#include <sstream>
#include <set>
#include <ctime>
#include <random>
#include "Document.hpp"


Document::Document(bool b, string d) {
    this->data = d;
    this->kshingles = DEFAULT_KSHINGLES;
}


Document::Document(string path) {
    this->path = path;
    this->kshingles = DEFAULT_KSHINGLES;

    ifstream docfile;
    docfile.open(this->path);

    if (docfile.is_open()) {
        this->valid = true;

        docfile.seekg(0, ios::end);
        this->data.reserve(docfile.tellg());
        docfile.seekg(0, ios::beg);
        this->data.assign((istreambuf_iterator<char>(docfile)), istreambuf_iterator<char>());

        docfile.close();

        if (this->data.length() < kshingles) {
            this->valid = false;
            cout << "The document is shorter than the minimum value of k" << endl;
        }

    } else {
        this->valid = false;
    }
}


string Document::get_permutation() const {
    if (this->data.length() == 0) return "";
    std::vector<std::string> words;
    std::string text = this->data;
    std::string::size_type beg = 0, end;

    do {
        end = text.find(' ', beg);
        if (end == std::string::npos) {
            end = text.size();
        }
        words.emplace_back(text.substr(beg, end - beg));
        beg = end + 1;
    } while (beg < text.size());

    random_device rd;
    mt19937 gen(rd());
    std::string res;
    uniform_int_distribution<> dis(0, words.size() - 1);
    for (int i = 0; i < words.size(); i++) {
        swap(words[i], words[(dis(gen) % (words.size() - i)) + i]);
        res.append(words[i]);
        if (i != words.size() - 1) res.append(" ");
    }
    return res;
}


vector<unsigned> Document::get_signature(vector<int> &c1, vector<int> &c2, unsigned HASH_FUNCTIONS) {
    set<unsigned> shingles = this->get_hashed_shingles(kshingles);
    vector<unsigned> sig(HASH_FUNCTIONS);
    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        sig[i] = UINT_MAX;
        for (unsigned shingle : shingles) {
            sig[i] = min(sig[i], fast_hash(c1[i], c2[i], shingle));
        }
    }
    return sig;
}


vector<Document *> Document::get_permutations(int k) const {
    std::vector<Document *> res;
    for (int i = 0; i < k; i++) {
        Document *temp = new Document(true, this->get_permutation());
        res.push_back(temp);
    }
    return res;
}


set<string> Document::get_shingles(unsigned k) const {
    set<string> res;
    for (unsigned i = 0; i <= this->data.length() - k; i++) {
        res.insert(this->data.substr(i, k));
    }
    return res;
}


set<unsigned> Document::get_hashed_shingles(unsigned k) const {
    set<unsigned> res;
    for (unsigned i = 0; i <= this->data.length() - k; i++) {
        string temp = this->data.substr(i, k);
        boost::crc_16_type h;
        h.process_bytes(temp.data(), temp.length());
        res.insert(h.checksum());
    }
    return res;
}


unsigned Document::fast_hash(int c1, int c2, unsigned val) {
    return (c1 * val + c2) % UINT_MAX;
}

#include <iostream>
#include <fstream>
#include <boost/functional/hash.hpp>

using namespace std;

#define BUCKETS 999


/**
 * Uses hash function with index i
 * http://stackoverflow.com/questions/24676237/generating-random-hash-functions-for-lsh-minhash-algorithm
 * http://stackoverflow.com/questions/19701052/how-many-hash-functions-are-required-in-a-minhash-algorithm/19711615#19711615
 *
 * @param i
 * @param buckets
 * @param val
 * @return
 */
unsigned hash(unsigned i, unsigned buckets, int val) {
    unsigned h1 = val % buckets;
    unsigned h2 = (2 * val + 1) % buckets;
    return (h1 + i * h2) % buckets;
}

double get_minhash_similarity(const string &doc1, const string &doc2){

    /* PSEUDOCODE
     * for each row r do begin
     *      for each hash function hi do
     *          compute hi(r)
     *      for each column c
     *          if c has 1 in row r
     *              for each hash function hi do
     *                  if hi(r) < M(i,c) then
     *                      M(i,c) = hi(r)
     */

    return 0.0;
}


int main(int argc, char *argv[]) {

    if (argc == 3) {
        ifstream docfile1, docfile2;

        docfile1.open(argv[1]);
        docfile2.open(argv[2]);

        if (not docfile1.is_open()) {
            cout << "Could not read first file." << endl;
            return -1;
        }

        if (not docfile2.is_open()) {
            cout << "Could not read second file." << endl;
            return -1;
        }

        string doc1, doc2;

        docfile1.seekg(0, ios::end);
        doc1.reserve(docfile1.tellg());
        docfile1.seekg(0, ios::beg);

        docfile2.seekg(0, ios::end);
        doc2.reserve(docfile2.tellg());
        docfile2.seekg(0, ios::beg);

        doc1.assign((istreambuf_iterator<char>(docfile1)), istreambuf_iterator<char>());
        doc2.assign((istreambuf_iterator<char>(docfile2)), istreambuf_iterator<char>());

        docfile1.close();
        docfile2.close();

        cout << get_minhash_similarity(doc1, doc2) << endl;

    } else {
        cout << "Invalid number of arguments" << endl;
    }

    boost::hash<string> string_hash;
    boost::hash<int> int_hash;

    unsigned long seed = 0;
    boost::hash_combine(seed, "Hash me");
    boost::hash_combine(seed, 2);

    cout << seed << endl;

}
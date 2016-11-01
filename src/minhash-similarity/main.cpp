#include <iostream>

using namespace std;

#define BUCKETS 999


/**
 * Uses hash function with index i
 * http://stackoverflow.com/questions/24676237/generating-random-hash-functions-for-lsh-minhash-algorithm
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


int main() {
    cout << "Hello world" << endl;
}
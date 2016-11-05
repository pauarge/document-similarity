#include "Comparator.hpp"

Comparator::Comparator(Document *doc1, Document *doc2) {
    this->doc1 = doc1;
    this->doc2 = doc2;
}


double Comparator::get_jaccard_similarity() {
    set<unsigned long> shingles1 = doc1->get_hashed_shingles(KSHINGLES);
    set<unsigned long> shingles2 = doc2->get_hashed_shingles(KSHINGLES);

    set<unsigned long> shingles_intersect;
    set_intersection(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
                     inserter(shingles_intersect, shingles_intersect.begin()));

    set<unsigned long> shingles_union;
    set_union(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
              inserter(shingles_union, shingles_union.begin()));

    return float(shingles_intersect.size()) / shingles_union.size();
}


double Comparator::get_minhash_similarity() {
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

    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    set<unsigned long> shingles1 = doc1->get_hashed_shingles(KSHINGLES);
    set<unsigned long> shingles2 = doc2->get_hashed_shingles(KSHINGLES);

    vector<unsigned long> sig1(HASH_FUNCTIONS);
    vector<unsigned long> sig2(HASH_FUNCTIONS);

    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        sig1[i] = ULONG_MAX;
        for (unsigned long shingle : shingles1) {
            sig1[i] = min(sig1[i], fast_hash(c1[i], c2[i], shingle));
        }
    }

    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        sig2[i] = ULONG_MAX;
        for (unsigned long shingle : shingles2) {
            sig2[i] = min(sig2[i], fast_hash(c1[i], c2[i], shingle));
        }
    }

    float common = 0;
    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        if (sig1[i] == sig2[i]) common++;
    }

    return common / HASH_FUNCTIONS;
}

/**
 * This implementation of generating might lead to duplicate coefficients, but the probability is so low that
 * checking if the coefficient already existed on the list is way more expensive than this margin of error.
 *
 * @param k
 * @return
 */
vector<int> Comparator::generate_random_coefficients() {
    vector<int> res(HASH_FUNCTIONS);

    for (int i = 0; i < HASH_FUNCTIONS; i++) {
        res[i] = rand();
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
unsigned long Comparator::fast_hash(int c1, int c2, unsigned long val) {
    return (c1 * val - 2 * c2) % ULONG_MAX;
}
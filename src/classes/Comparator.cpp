#include "Comparator.hpp"

Comparator::Comparator(Document *doc1, Document *doc2) {
    this->doc1 = doc1;
    this->doc2 = doc2;
}


double Comparator::get_jaccard_similarity() {
    set<unsigned> shingles1 = doc1->get_hashed_shingles(KSHINGLES);
    set<unsigned> shingles2 = doc2->get_hashed_shingles(KSHINGLES);

    set<unsigned> shingles_intersect;
    set_intersection(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
                     inserter(shingles_intersect, shingles_intersect.begin()));

    set<unsigned> shingles_union;
    set_union(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
              inserter(shingles_union, shingles_union.begin()));

    return float(shingles_intersect.size()) / shingles_union.size();
}


double Comparator::get_minhash_similarity() {
    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<unsigned> sig1 = doc1->get_signature(c1, c2);
    vector<unsigned> sig2 = doc2->get_signature(c1, c2);

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

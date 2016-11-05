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
    set<int> coe = generate_random_coefficients(5);
    return 0.0;
}


set<int> Comparator::generate_random_coefficients(int k) {
    set<int> res;

    for (int i = 0; i < k; i++) {
        int val = rand();
        pair<set<int>::iterator, bool> p = res.insert(val);

        // Ensuring value did not exist previously
        while(not p.second){
            val = 1;
            p = res.insert(val);
        }
    }

    return res;
}
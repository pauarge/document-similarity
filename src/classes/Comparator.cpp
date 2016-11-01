#include "Comparator.hpp"


double Comparator::get_jaccard_similarity() {
    set<string> shingles1 = doc1->get_shingles(KSHINGLES);
    set<string> shingles2 = doc2->get_shingles(KSHINGLES);

    set<string> shingles_intersect;
    set_intersection(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
                     inserter(shingles_intersect, shingles_intersect.begin()));

    set<string> shingles_union;
    set_union(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
              inserter(shingles_union, shingles_union.begin()));

    return float(shingles_intersect.size()) / shingles_union.size();
}

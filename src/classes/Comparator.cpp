#include "Comparator.hpp"


Comparator::Comparator(Document *doc1, Document *doc2) {
    this->doc1 = doc1;
    this->doc2 = doc2;
    this->threshold = pow((1 / (float) BANDS), (1 / (float) ROWS));
}

Comparator::Comparator(vector<Document*> V) {
    this->docs = V;
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

double Comparator::get_lsh_similarity() {
    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<unsigned> sig1 = doc1->get_signature(c1, c2);
    vector<unsigned> sig2 = doc2->get_signature(c1, c2);

    vector<unsigned> lsh1 = get_bands(sig1);
    vector<unsigned> lsh2 = get_bands(sig2);
    float common = 0;
    for (int i = 0; i < BANDS; ++i) {
        if (lsh1[i] == lsh2[i]) ++common;
    }
    if (common / BANDS >= threshold) {
        common = 0;
        for (int i = 0; i < HASH_FUNCTIONS; i++) {
            if (sig1[i] == sig2[i]) common++;
        }
        return common / HASH_FUNCTIONS;
    } else return 0;
}

vector<unsigned> Comparator::get_bands(vector<unsigned> &sig) {
    vector<unsigned> lsh;
    for (int i = 0; i < HASH_FUNCTIONS; i += ROWS) {
        size_t seed = 0;
        vector<unsigned> v(ROWS);
        for (int j = 0; j < ROWS; ++j) {
            v[j] = sig[i + j];
        }
        boost::hash_combine(seed, v);
        lsh.push_back(seed);
    }
    return lsh;
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

vector<vector<double> > Comparator::get_multi_jaccard_similarity() {
    vector<vector<double>> Res(this->docs.size(), vector<double> (this->docs.size()));
    for (int i = 0; i < this->docs.size()-1; i++) {
        for (int j = i; j < this->docs.size()-1; j++) {
            Document doc1 = *(this->docs[i]);
            Document doc2 = *(this->docs[i+1]);
            Comparator c = Comparator(&doc1, &doc2);
            Res[i][j] = Res[j][i] = c.get_jaccard_similarity();
        }
    }
    return Res;
}

vector<vector<double> > Comparator::get_multi_minhash_similarity() {
    vector<vector<double>> Res(this->docs.size(), vector<double> (this->docs.size()));
    for (int i = 0; i < this->docs.size()-1; i++) {
        for (int j = i; j < this->docs.size()-1; j++) {
            Document doc1 = *(this->docs[i]);
            Document doc2 = *(this->docs[i+1]);
            Comparator c = Comparator(&doc1, &doc2);
            Res[i][j] = Res[j][i] = c.get_minhash_similarity();
        }
    }
    return Res;
}

vector<vector<double> > Comparator::get_multi_lsh_similarity() {
    vector<vector<double>> Res(this->docs.size(), vector<double> (this->docs.size()));
    for (int i = 0; i < this->docs.size()-1; i++) {
        for (int j = i; j < this->docs.size()-1; j++) {
            Document doc1 = *(this->docs[i]);
            Document doc2 = *(this->docs[i+1]);
            Comparator c = Comparator(&doc1, &doc2);
            Res[i][j] = Res[j][i] = c.get_lsh_similarity();
        }
    }
    return Res;
}

#include <algorithm>
#include "Comparator.hpp"


Comparator::Comparator(vector<Document *> V) {
    this->docs = V;
    this->HASH_FUNCTIONS = DEFAULT_HASH_FUNCTIONS;
    this->threshold = pow((1 / (float) BANDS), (1 / (float) ROWS));
    this->BANDS = DEFAULT_BANDS;
    this->ROWS = DEFAULT_ROWS;
}

vector<vector<double>> Comparator::get_lsh_similarity() {
    vector<vector<double>> res(docs.size(), vector<double>(docs.size()));

    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<vector<unsigned>> signatures(this->docs.size());
    vector<vector<unsigned>> lsh(signatures.size());
    for (int i = 0; i < this->docs.size(); i++) {
        signatures[i] = this->docs[i]->get_signature(c1, c2, HASH_FUNCTIONS);
        lsh[i] = get_bands(signatures[i]);
    }

    for (int i = 0; i < docs.size(); ++i) {
        for (int j = i; j < docs.size(); ++j) {
            if (i == j) res[i][j] = 1;
            else {
                float common = 0;
                for (int k = 0; k < BANDS; ++k) {
                    if (lsh[i][k] == lsh[j][k]) ++common;
                }
                if (common / BANDS >= threshold / 2) {
                    common = 0;
                    for (int t = 0; t < HASH_FUNCTIONS; t++) {
                        if (signatures[i][t] == signatures[j][t]) common++;
                    }
                    res[i][j] = res[j][i] = common / HASH_FUNCTIONS;
                } else res[i][j] = res[j][i] = 0;
            }
        }
    }
    return res;
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

vector<vector<double>> Comparator::get_jaccard_similarity() {
    vector<vector<double>> Res(this->docs.size(), vector<double>(this->docs.size()));

    vector<set<unsigned>> shingles(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        shingles[i] = this->docs[i]->get_shingles(KSHINGLES);
    }

    for (int i = 0; i < this->docs.size(); i++) {
        for (int j = i; j < this->docs.size(); j++) {
            set<unsigned> shingles_intersect;
            set_intersection(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                             inserter(shingles_intersect, shingles_intersect.begin()));

            set<unsigned> shingles_union;
            set_union(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                      inserter(shingles_union, shingles_union.begin()));
            Res[i][j] = Res[j][i] = float(shingles_intersect.size()) / shingles_union.size();
        }
    }
    return Res;
}

vector<vector<double>> Comparator::get_minhash_similarity() {
    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<vector<unsigned>> signatures(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        signatures[i] = this->docs[i]->get_signature(c1, c2, HASH_FUNCTIONS);
    }

    vector<vector<double>> Res(this->docs.size(), vector<double>(this->docs.size()));
    for (int i = 0; i < this->docs.size(); i++) {
        for (int j = i; j < this->docs.size(); j++) {
            float common = 0;
            for (int h = 0; h < HASH_FUNCTIONS; h++) {
                if (signatures[i][h] == signatures[j][h]) common++;
            }
            Res[i][j] = Res[j][i] = common / HASH_FUNCTIONS;
        }
    }
    return Res;
}

void Comparator::setHashFunctions(unsigned n) {
    this->HASH_FUNCTIONS = n;
}

void Comparator::setBandsRows(unsigned b, unsigned r) {
    this->BANDS = b;
    this->ROWS = r;
}

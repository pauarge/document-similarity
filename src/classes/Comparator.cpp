#include <algorithm>
#include "Comparator.hpp"


Comparator::Comparator(vector<Document *> V) {
    this->docs = V;
    this->hash_functions = DEFAULT_HASH_FUNCTIONS;
    this->bands = DEFAULT_BANDS;
    this->rows = DEFAULT_ROWS;
    this->threshold = pow((1 / (float) bands), (1 / (float) rows));
}


void Comparator::set_hash_functions(unsigned n) {
    this->hash_functions = n;
}


void Comparator::set_bands_rows(unsigned b, unsigned r) {
    this->bands = b;
    this->rows = r;
}


vector<vector<double>> Comparator::get_jaccard_similarity() {
    vector<vector<double>> res(this->docs.size(), vector<double>(this->docs.size()));

    vector<set<string>> shingles(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        shingles[i] = this->docs[i]->get_shingles(docs[0]->kshingles);
    }

    for (int i = 0; i < this->docs.size(); i++) {
        for (int j = i; j < this->docs.size(); j++) {
            set<string> shingles_intersect;
            set_intersection(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                             inserter(shingles_intersect, shingles_intersect.begin()));

            set<string> shingles_union;
            set_union(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                      inserter(shingles_union, shingles_union.begin()));
            res[i][j] = res[j][i] = float(shingles_intersect.size()) / shingles_union.size();
        }
    }
    return res;
}


vector<vector<double>> Comparator::get_hashed_jaccard_similarity() {
    vector<vector<double>> res(this->docs.size(), vector<double>(this->docs.size()));

    vector<set<unsigned>> shingles(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        shingles[i] = this->docs[i]->get_hashed_shingles(docs[0]->kshingles);
    }

    for (int i = 0; i < this->docs.size(); i++) {
        for (int j = i; j < this->docs.size(); j++) {
            set<unsigned> shingles_intersect;
            set_intersection(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                             inserter(shingles_intersect, shingles_intersect.begin()));

            set<unsigned> shingles_union;
            set_union(shingles[i].begin(), shingles[i].end(), shingles[j].begin(), shingles[j].end(),
                      inserter(shingles_union, shingles_union.begin()));
            res[i][j] = res[j][i] = float(shingles_intersect.size()) / shingles_union.size();
        }
    }
    return res;
}


vector<vector<double>> Comparator::get_minhash_similarity() {
    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<vector<unsigned>> signatures(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        signatures[i] = this->docs[i]->get_signature(c1, c2, hash_functions);
    }

    vector<vector<double>> res(this->docs.size(), vector<double>(this->docs.size()));
    for (int i = 0; i < this->docs.size(); i++) {
        for (int j = i; j < this->docs.size(); j++) {
            float common = 0;
            for (int h = 0; h < hash_functions; h++) {
                if (signatures[i][h] == signatures[j][h]) common++;
            }
            res[i][j] = res[j][i] = common / hash_functions;
        }
    }
    return res;
}


vector<vector<double>> Comparator::get_lsh_similarity() {
    vector<vector<double>> res(docs.size(), vector<double>(docs.size()));

    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<vector<unsigned>> signatures(this->docs.size());
    vector<vector<unsigned>> lsh(signatures.size());
    for (int i = 0; i < this->docs.size(); i++) {
        signatures[i] = this->docs[i]->get_signature(c1, c2, hash_functions);
        lsh[i] = get_bands(signatures[i]);
    }

    for (int i = 0; i < docs.size(); ++i) {
        for (int j = i; j < docs.size(); ++j) {
            if (i == j) res[i][j] = 1;
            else {
                float common = 0;
                for (int k = 0; k < bands; ++k) {
                    if (lsh[i][k] == lsh[j][k]) ++common;
                }
                if (common / bands >= threshold / 2) {
                    common = 0;
                    for (int t = 0; t < hash_functions; t++) {
                        if (signatures[i][t] == signatures[j][t]) common++;
                    }
                    res[i][j] = res[j][i] = common / hash_functions;
                } else res[i][j] = res[j][i] = 0;
            }
        }
    }
    return res;
}


vector<vector<double>> Comparator::get_advanced_lsh_similarity() {
    vector<vector<double>> res(docs.size(), vector<double>(docs.size()));

    vector<int> c1 = generate_random_coefficients();
    vector<int> c2 = generate_random_coefficients();

    vector<vector<unsigned>> signatures(this->docs.size());
    vector<vector<unsigned>> lsh(this->docs.size());
    for (int i = 0; i < this->docs.size(); i++) {
        signatures[i] = this->docs[i]->get_signature(c1, c2, hash_functions);
        lsh[i] = get_bands(signatures[i]);
    }

    for (int i = 0; i < docs.size(); ++i) {
        for (int j = i; j < docs.size(); ++j) {
            if (i == j) res[i][j] = 0;
            else {
                float common = 0;
                for (int k = 0; k < bands; ++k) {
                    if (lsh[i][k] == lsh[j][k]) ++common;
                }
                if (common / bands >= threshold / 2) {
                    res[i][j] = res[j][i] = get_levenshtein_distance(docs[i]->data, docs[j]->data);
                } else res[i][j] = res[j][i] = -1;
            }
        }
    }
    return res;
}


int Comparator::get_levenshtein_distance(const string &s1, const string &s2) {
    unsigned N1 = s1.size();
    unsigned N2 = s2.size();
    int i, j;
    vector<int> T(N2 + 1);

    for (i = 0; i <= N2; i++) {
        T[i] = i;
    }
    for (i = 0; i < N1; i++) {
        T[0] = i + 1;
        int corner = i;
        for (j = 0; j < N2; j++) {
            int upper = T[j + 1];
            if (s1[i] == s2[j])
                T[j + 1] = corner;
            else {
                T[j + 1] = min(T[j], min(upper, corner)) + 1;
            }
            corner = upper;
        }
    }
    return T[N2];
}


vector<unsigned> Comparator::get_bands(vector<unsigned> &sig) {
    vector<unsigned> lsh;
    for (int i = 0; i < hash_functions; i += rows) {
        size_t seed = 0;
        vector<unsigned> v(rows);
        for (int j = 0; j < rows; ++j) {
            v[j] = sig[i + j];
        }
        boost::hash_combine(seed, v);
        lsh.push_back(seed);
    }
    return lsh;
}


vector<int> Comparator::generate_random_coefficients() {
    vector<int> res(hash_functions);
    for (int i = 0; i < hash_functions; i++) {
        res[i] = rand();
    }
    return res;
}
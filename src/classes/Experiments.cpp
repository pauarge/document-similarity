#include "Experiments.hpp"


Experiments::Experiments() {

}


void Experiments::experiment_kshingles(vector<Document *> &docs) {
    for (unsigned i = 0; i < 10; ++i) {
        docs[0]->kshingles = i + 1;
        Comparator comparator = Comparator(docs);
        clock_t begin = clock();
        cout << "Jaccard similarity with KSHINGLES = " << i + 1 << endl;
        vector<vector<double>> jaccard_res = comparator.get_jaccard_similarity();
        print_matrix(jaccard_res);
        cout << "Calculated in " << get_time(begin) << " seconds." << endl << endl;
    }
}


void Experiments::experiment_parametres_lsh(Comparator comparator) {

    unsigned U[20] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200};

    for (int u = 0; u < 20; u++) {
        unsigned y = U[u];
        double differ = 0;
        cout << "=== TRYING " << y << " HASH FUNCTIONS ===" << endl;
        comparator.set_hash_functions(y);
        unsigned v[6] = {y / 2, 2, y / 5, 5, y / 10, 10};
        clock_t x = clock();
        vector<vector<double>> min_res = comparator.get_minhash_similarity();
        double t1 = get_time(x);

        for (int i = 0; i < 6; i += 2) {

            comparator.set_bands_rows(v[i], v[i + 1]);

            clock_t begin = clock();
            cout << "LSH similarity Bands = " << v[i] << " Rows = " << v[i + 1] << endl;
            vector<vector<double>> lsh_res = comparator.get_lsh_similarity();
            double t2 = get_time(begin);

            double diff = 0;
            for (int n = 0; n < lsh_res.size(); n++) {
                for (int m = 0; m < lsh_res.size(); m++) {
                    diff += abs(lsh_res[n][m] - min_res[n][m]);
                }
            }
            differ += diff / (double(lsh_res.size() * lsh_res.size()));
            cout << "Avg Difference: " << diff / (double(lsh_res.size() * lsh_res.size())) << endl;
            if (i == 4) std::cout << "Avg Difference for the group: " << differ / 3 << endl;
            cout << "Time Minhash - LSH " << t1 - t2 << " s" << endl << endl;
        }
    }
}


double Experiments::get_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    return elapsed;
}

#include "Experiments.hpp"


void print_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Calculated in " << elapsed << " seconds." << endl << endl;
}

void experiment_hashFunctions (Comparator comparator, int n) {

    for (int k = 25; k < 500; k += 25) {
        #undef HASH_FUNCTIONS
        #define HASH_FUNCTIONS k

        cout << k << " Hash functions" << endl;

        clock_t begin = clock();
        cout << "Jaccard similarity" << endl;
        vector<vector<double>> jaccard_res = comparator.get_jaccard_similarity();
        print_time(begin);

        begin = clock();
        cout << "Minhash similarity" << endl;
        vector<vector<double>> minhash_res = comparator.get_minhash_similarity();
        print_time(begin);

        float diff = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                diff += abs(jaccard_res[i][j] - minhash_res[i][j]);
            }
        }
        cout << "Precision total deviation (between Jaccard and Minhash): " << diff << endl;
    }
}
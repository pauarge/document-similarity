#include "Experiments.hpp"


double Experiments::print_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    return elapsed;
}

void Experiments::experiment_hashFunctions(Comparator comparator, unsigned n) {

    for (unsigned k = 25; k <= 500; k += 25) {

        comparator.setHashFunctions(k);

        cout << k << " Hash functions " << endl;

        clock_t begin = clock();
        vector<vector<double>> jaccard_res = comparator.get_jaccard_similarity();
        double t1 = print_time(begin);

        begin = clock();
        vector<vector<double>> minhash_res = comparator.get_minhash_similarity();
        double t2 = print_time(begin);

        cout << "Difference Jaccard - Minhash = " << t1 - t2;
        float diff = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                diff += abs(jaccard_res[i][j] - minhash_res[i][j]);
            }
        }
        cout << " Desviation (between Jaccard and Minhash): " << diff << endl;
    }
}

Experiments::Experiments() {

}

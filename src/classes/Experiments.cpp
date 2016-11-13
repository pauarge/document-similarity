#include "Experiments.hpp"


double Experiments::print_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    return elapsed;
}

Experiments::Experiments() {

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


void Experiments::experiment_parametresLSH(Comparator comparator) {

    unsigned v[6] = {50,2,25,4,10,10}; ///En el cas que escollissim hashfunctions = 100

    clock_t x = clock();
    vector<vector<double>> min_res = comparator.get_minhash_similarity();
    double t1 = print_time(x);
    for (vector<double> V : min_res) {
        for (double x : V) {
            cout << x << " ";
        }
        cout << endl;
    }
    cout << endl;

    for(int i = 0; i < 6; i += 2) {

        comparator.setBandsRows(v[i], v[i+1]);

        clock_t begin = clock();
        cout << "LSH similarity Bands = " << v[i] << " Rows = " << v[i+1] << endl;
        vector<vector<double>> lsh_res = comparator.get_lsh_similarity();
        double t2 = print_time(begin);
        for (vector<double> V : lsh_res) {
            for (double x : V) {
                cout << x << " ";
            }
            cout << endl;
        }
        cout << "Time Minhash - LSH "<< t1 - t2 << " s" << endl << endl;
    }
}

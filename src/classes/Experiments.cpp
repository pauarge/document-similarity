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

    unsigned U[20] = {10,20,30,40,50,60,70,80,90,100,110,120,130,140,150,160,170,180,190,200};

    for (int u = 0; u < 20; u++) {
        unsigned y = U[u];
        double differ = 0;
        cout << "=== TRYING " << y << " HASH FUNCTIONS ===" << endl;
        comparator.setHashFunctions(y);
        unsigned v[6] = {y/2,2,y/5,5,y/10,10};
        clock_t x = clock();
        vector<vector<double>> min_res = comparator.get_minhash_similarity();
        double t1 = print_time(x);


        for(int i = 0; i < 6; i += 2) {

            comparator.setBandsRows(v[i], v[i+1]);

            clock_t begin = clock();
            cout << "LSH similarity Bands = " << v[i] << " Rows = " << v[i+1] << endl;
            vector<vector<double>> lsh_res = comparator.get_lsh_similarity();
            double t2 = print_time(begin);

            double diff = 0;
            for (int n = 0; n < lsh_res.size(); n++) {
                for (int m = 0; m < lsh_res.size(); m++) {
                    diff += abs(lsh_res[n][m] - min_res[n][m]);
                }
            }
            differ += diff/(double(lsh_res.size()*lsh_res.size()));
            cout << "Avg Difference: " << diff/(double(lsh_res.size()*lsh_res.size())) << endl;
            if (i == 4) std::cout << "Avg Difference for the group: " << differ/3 << endl;
            cout << "Time Minhash - LSH "<< t1 - t2 << " s" << endl << endl;
        }
    }
}

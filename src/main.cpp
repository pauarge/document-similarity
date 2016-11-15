#include "classes/Comparator.hpp"
#include "utils/utils.hpp"


int main(int argc, char *argv[]) {

    if (argc == 2) {

        unsigned td, sh, hf, ba, ro;

        cout << "Enter number of permutations for each document [default 0]" << endl;
        cin >> td;

        cout << "Enter length of shingles [default 9]" << endl;
        cin >> sh;

        cout << "Enter # of hash functions for Minhash [default 50]" << endl;
        cin >> hf;

        cout << "Enter # of bands for LSH [default 25]" << endl;
        cin >> ba;

        cout << "Enter # of rows for LSH [default 2]" << endl;
        cin >> ro;

        vector<Document *> docs = get_docs_from_path(argv[1], td, sh);
        Comparator comparator = Comparator(docs, hf, ba, ro);

        clock_t begin = clock();
        cout << "Calculating Jaccard similarity..." << endl;
        vector<vector<double>> jaccard_res = comparator.get_hashed_jaccard_similarity();
        print_matrix(jaccard_res);
        print_time(begin);

        begin = clock();
        cout << "Calculating minhash similarity..." << endl;
        vector<vector<double>> minhash_res = comparator.get_minhash_similarity();
        print_matrix(minhash_res);
        print_time(begin);

        begin = clock();
        cout << "Calculating LSH similarity..." << endl;
        vector<vector<double>> lsh_res = comparator.get_lsh_similarity();
        print_matrix(lsh_res);
        print_time(begin);

        begin = clock();
        cout << "Calculating advanced LSH similarity..." << endl;
        vector<vector<double>> lshAdvanced_res = comparator.get_advanced_lsh_similarity();
        print_matrix(lshAdvanced_res);
        print_time(begin);

        float diff = 0;
        for (int i = 0; i < docs.size(); i++) {
            for (int j = 0; j < docs.size(); j++) {
                diff += abs(jaccard_res[i][j] - minhash_res[i][j]);
            }
        }
        cout << "Precision total deviation (between Jaccard and Minhash): " << diff << endl;


    } else {
        cout << "Invalid number of arguments" << endl;
    }

}

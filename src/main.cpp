#include "classes/Comparator.hpp"
#include "utils/utils.hpp"


int main(int argc, char *argv[]) {

    if (argc == 2) {
        vector<Document *> docs = get_docs_from_path(argv[1]);
        Comparator comparator = Comparator(docs);

        clock_t begin = clock();
        cout << "Jaccard similarity" << endl;

        vector<vector<double>> jaccard_res = comparator.get_hashed_jaccard_similarity();
        print_matrix(jaccard_res);
        print_time(begin);

        begin = clock();
        cout << "Minhash similarity" << endl;
        vector<vector<double>> minhash_res = comparator.get_minhash_similarity();
        print_matrix(minhash_res);
        print_time(begin);

        begin = clock();
        cout << "LSH similarity" << endl;
        vector<vector<double>> lsh_res = comparator.get_lsh_similarity();
        print_matrix(lsh_res);
        print_time(begin);

        begin = clock();
        cout << "LSH advanced similarity" << endl;
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

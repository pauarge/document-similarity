#include <ctime>
#include "classes/Comparator.hpp"


void print_time(clock_t begin){
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Calculated in " << elapsed << " seconds." << endl << endl;
}


int main(int argc, char *argv[]) {

    // TODO: Add time measuring features

    if (argc == 3) {
        Document doc1 = Document(argv[1]);
        Document doc2 = Document(argv[2]);

        if (not doc1.valid) {
            cout << "Could not read first file." << endl;
            return -1;
        }

        if (not doc2.valid) {
            cout << "Could not read second file." << endl;
            return -1;
        }

        Comparator comparator = Comparator(&doc1, &doc2);

        clock_t begin = clock();
        cout << "Jaccard similarity " << comparator.get_jaccard_similarity() << endl;
        print_time(begin);

        begin = clock();
        cout << "Minhash similarity " << comparator.get_minhash_similarity() << endl;
        print_time(begin);

        begin = clock();
        cout << "LSH similarity " << comparator.get_lsh_similarity() << endl;
        print_time(begin);

    } else {
        cout << "Invalid number of arguments" << endl;
    }

}

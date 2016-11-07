#include <ctime>
#include <boost/filesystem.hpp>
#include "classes/Comparator.hpp"

namespace fs = ::boost::filesystem;


void print_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Calculated in " << elapsed << " seconds." << endl << endl;
}


int main(int argc, char *argv[]) {

    // TODO: Add time measuring features

    if (argc == 2) {
        srand(time(NULL));
        string path = argv[2];
        if (!fs::exists(path) || !fs::is_directory(path)) {
            cout << "Could not read directory" << endl;
        }

        fs::recursive_directory_iterator it(path);
        fs::recursive_directory_iterator endit;
        vector<Document *> docs;

        while (it != endit) {
            if (fs::is_regular_file(*it) and it->path().extension() == "txt") {
                Document doc = Document(it->path().string());
                if (doc.valid) {
                    docs.push_back(&doc);
                }
            }
            it++;
        }

        Comparator comparator = Comparator(docs);

        /*
        clock_t begin = clock();
        cout << "Jaccard similarity " << comparator.get_jaccard_similarity() << endl;
        print_time(begin);

        begin = clock();
        cout << "Minhash similarity " << comparator.get_minhash_similarity() << endl;
        print_time(begin);

        begin = clock();
        cout << "LSH similarity " << comparator.get_lsh_similarity() << endl;
        print_time(begin);
         */

    } else {
        cout << "Invalid number of arguments" << endl;
    }

}

#include <ctime>
#include <boost/filesystem.hpp>
#include "Comparator.hpp"
#include "Experiments.hpp"

namespace fs = ::boost::filesystem;


int main(int argc, char *argv[]) {

    if (argc == 2) {
        string path = argv[1];

        if (!fs::exists(path) || !fs::is_directory(path)) {
            cout << "Could not read directory" << endl;
        }

        clock_t begin = clock();
        cout << "Generating documents" << endl;

        fs::recursive_directory_iterator it(path);
        fs::recursive_directory_iterator endit;
        vector<Document *> docs;

        while (it != endit) {
            if (fs::is_regular_file(*it) and it->path().extension() == ".txt") {
                Document *doc = new Document(it->path().string());
                if (doc->valid) {
                    docs.push_back(doc);
                    vector<Document *> temp = doc->get_permutations(TEST_DOCS);
                    docs.insert(docs.end(), temp.begin(), temp.end());
                }
            }
            it++;
        }
        print_time(begin);

        Comparator comparator = Comparator(docs);

        int n;
        cin >> n;
        while(n != 0) {
            switch(n) {
                case 1:
                    experiment_k(comparator, docs.size());
                    break;
            }
            cin >> n;
        }
    } else {
        cout << "Invalid number of arguments" << endl;
    }
}


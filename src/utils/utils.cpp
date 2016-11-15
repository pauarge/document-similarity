#include "utils.hpp"


void print_time(clock_t begin) {
    clock_t end = clock();
    double elapsed = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Calculated in " << elapsed << " seconds." << std::endl << std::endl;
}


void print_matrix(vector<vector<double>> &M){
    for (vector<double> V : M) {
        for (double d : V) {
            cout << d << " ";
        }
        cout << endl;
    }
}


// TODO: Crash if could not read directory
vector<Document *> get_docs_from_path(string path) {
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
    return docs;
}

#include "classes/Comparator.hpp"
#include "classes/Experiments.hpp"
#include "utils/utils.hpp"


int main(int argc, char *argv[]) {

    if (argc == 2) {
        vector<Document *> docs = get_docs_from_path(argv[1]);
        Comparator comparator = Comparator(docs);
        Experiments experiment = Experiments();
        experiment.experiment_hashFunctions(comparator, docs.size());
    } else {
        cout << "Invalid number of arguments" << endl;
    }
}


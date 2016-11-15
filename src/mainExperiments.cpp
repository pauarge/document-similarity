#include "classes/Comparator.hpp"
#include "classes/Experiments.hpp"
#include "utils/utils.hpp"

int main(int argc, char *argv[]) {

    if (argc == 2) {

        vector<Document *> docs = get_docs_from_path(argv[1]);
        Experiments experiment = Experiments();
        /*
        experiment.experiment_kshingles(docs);
        Comparator comparator = Comparator(docs);
        experiment.experiment_parametresLSH(comparator);*/
        experiment.experiment_hashed_shingles(docs);

    } else {
        cout << "Invalid number of arguments" << endl;
    }
}


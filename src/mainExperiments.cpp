#include "classes/Comparator.hpp"
#include "classes/Experiments.hpp"


int main(int argc, char *argv[]) {

    if (argc == 2) {

        vector<Document *> docs = get_docs_from_path(argv[1]);
        Comparator comparator = Comparator(docs);
        Experiments experiment = Experiments();

        cout << "Select experiment: " << endl;
        cout << "1 - KSHINGLES" << endl;
        cout << "2 - LSH params" << endl;
        cout << "3 - Hashed shingles" << endl;

        unsigned e;

        while (cin >> e) {
            switch (e) {
                case 1:
                    experiment.experiment_kshingles(docs);
                    break;
                case 2:
                    experiment.experiment_parametres_lsh(comparator);
                    break;
                case 3:
                    experiment.experiment_hashed_shingles(docs);
                    break;
                default:
                    cout << "Command not defined" << endl;
                    break;
            }
        }

    } else {
        cout << "Invalid number of arguments" << endl;
    }
}


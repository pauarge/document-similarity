#include <iostream>
#include "classes/Comparator.hpp"
#include "classes/Document.hpp"

using namespace std;


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

        set<unsigned> s = doc1.get_hashed_shingles(5);

        cout << "Jaccard similarity " << comparator.get_jaccard_similarity() << endl;

    } else {
        cout << "Invalid number of arguments" << endl;
    }

}

//
// Created by ruben on 7/11/16.
//
#include <vector>
#include <iostream>
#include "classes/Document.hpp"
#include "classes/Comparator.hpp"

int main() {

    Document doc1(true, "this is the first test");
    Document doc2(true, "this is the second test");

    std::vector<Document*> docs;
    docs.push_back(&doc1);
    docs.push_back(&doc2);

    Comparator mycomp = Comparator(docs);
    vector< vector<double> > D(2, vector<double> (2));
    D = mycomp.get_multi_jaccard_similarity();
    for (vector<double> V : D) {
        for (double d : V) {
            cout << d << " " ;
        }
        cout << endl;
    }
}

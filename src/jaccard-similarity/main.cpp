#include <iostream>
#include <fstream>
#include <set>

using namespace std;

#define KSHINGLES 5


set<string> get_shingles(unsigned k, const string &doc) {
    set<string> res;
    for (unsigned long i = 0; i <= doc.length() - k; i++) {
        string temp = doc.substr(i, k);
        res.insert(temp);
    }
    return res;
}


double get_jaccard(const string &doc1, const string &doc2) {
    set<string> shingles1 = get_shingles(KSHINGLES, doc1);
    set<string> shingles2 = get_shingles(KSHINGLES, doc2);

    set<string> shingles_intersect;
    set_intersection(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
                     inserter(shingles_intersect, shingles_intersect.begin()));

    set<string> shingles_union;
    set_union(shingles1.begin(), shingles1.end(), shingles2.begin(), shingles2.end(),
              inserter(shingles_union, shingles_union.begin()));

    return float(shingles_intersect.size()) / shingles_union.size();
}


int main(int argc, char *argv[]) {

    if (argc == 3) {
        ifstream docfile1, docfile2;

        docfile1.open(argv[1]);
        docfile2.open(argv[2]);

        if (not docfile1.is_open()) {
            cout << "Could not read first file." << endl;
            return -1;
        }

        if (not docfile2.is_open()) {
            cout << "Could not read second file." << endl;
            return -1;
        }

        string doc1, doc2;

        docfile1.seekg(0, ios::end);
        doc1.reserve(docfile1.tellg());
        docfile1.seekg(0, ios::beg);

        docfile2.seekg(0, ios::end);
        doc2.reserve(docfile2.tellg());
        docfile2.seekg(0, ios::beg);

        doc1.assign((istreambuf_iterator<char>(docfile1)), istreambuf_iterator<char>());
        doc2.assign((istreambuf_iterator<char>(docfile2)), istreambuf_iterator<char>());

        docfile1.close();
        docfile2.close();

        cout << get_jaccard(doc1, doc2) << endl;
    } else {
        cout << "Invalid number of arguments" << endl;
    }

}
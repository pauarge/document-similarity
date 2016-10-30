#include <iostream>
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


int main() {

    string doc1 = "Hola em dic pau";
    string doc2 = "Hola em dic Manel";

    cout << get_jaccard(doc1, doc2) << endl;

}
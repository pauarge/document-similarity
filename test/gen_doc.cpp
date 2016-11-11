#include <vector>
#include <iostream>
#include <fstream>
#include "../src/classes/Document.hpp"

int main() {
    Document d(true, "From Donald Trump’s triumph to the rise of a new caliphate in the Middle East, the tension is likely to get worse before it gets better. In the US, Trump played on middle class and working class fears about immigration and cultural nostalgia for a bygone era in America");
    vector<std::string> docs;
    int i = 0;
    while (i < 20) {
        std::string cand = d.get_permutation();
        int j;
        for (j = 0; j < docs.size(); j++) if (docs[j] == cand) break;
        if (j == docs.size()) {
            std::cout << cand << std::endl << std::endl;
            docs.push_back(cand);
            ++i;
            std::string name = "doc"+to_string(i)+".txt";
            ofstream myfile;
            myfile.open (name);
            myfile << cand << "\n";
            myfile.close();
        }
    }
}

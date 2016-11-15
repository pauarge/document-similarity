#include "Comparator.hpp"


#ifndef DOCUMENT_SIMILARITY_EXPERIMENTS_H
#define DOCUMENT_SIMILARITY_EXPERIMENTS_H

class Experiments {

public:

    Experiments();

    double print_time(clock_t begin);

    void experiment_kshingles(vector<Document *> &docs);

    void experiment_parametresLSH(Comparator comparator);

};

#endif
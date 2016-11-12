#include "Comparator.hpp"


#ifndef DOCUMENT_SIMILARITY_EXPERIMENTS_H
#define DOCUMENT_SIMILARITY_EXPERIMENTS_H

class Experiments {

public:

    Experiments();

    double print_time(clock_t begin);

    void experiment_hashFunctions(Comparator comparator, unsigned n);

};

#endif
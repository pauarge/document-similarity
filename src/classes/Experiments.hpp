#include "Comparator.hpp"


#ifndef DOCUMENT_SIMILARITY_EXPERIMENTS_H
#define DOCUMENT_SIMILARITY_EXPERIMENTS_H

class Experiments {

public:

    void static print_time(clock_t begin);

    void static experiment_hashFunctions(Comparator comparator, unsigned n);

};

#endif
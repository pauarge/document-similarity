#include "Comparator.hpp"
#include "../utils/utils.hpp"


#ifndef DOCUMENT_SIMILARITY_EXPERIMENTS_H
#define DOCUMENT_SIMILARITY_EXPERIMENTS_H

class Experiments {

public:

    Experiments();

    void experiment_kshingles(vector<Document *> &docs);

    void experiment_parametres_lsh(Comparator comparator);

    void experiment_hashed_shingles(vector<Document *> &docs);

private:
    double get_time(clock_t begin);

};

#endif
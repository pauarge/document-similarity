#include <iostream>
#include <ctime>
#include <boost/filesystem.hpp>
#include "../classes/Document.hpp"

namespace fs = ::boost::filesystem;

#ifndef DOCUMENT_SIMILARITY_UTILS_HPP
#define DOCUMENT_SIMILARITY_UTILS_HPP

void print_time(clock_t begin);

void print_matrix(vector<vector<double>> &M);

vector<Document *> get_docs_from_path(string path, unsigned test_docs, unsigned shingles);

#endif

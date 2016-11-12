#include <iostream>
#include <ctime>
#include <boost/filesystem.hpp>
#include "../classes/Document.hpp"

namespace fs = ::boost::filesystem;

#ifndef DOCUMENT_SIMILARITY_UTILS_HPP
#define DOCUMENT_SIMILARITY_UTILS_HPP

void print_time(clock_t begin);

vector<Document *> get_docs_from_path(string path);

#endif

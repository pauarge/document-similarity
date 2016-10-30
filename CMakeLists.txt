cmake_minimum_required(VERSION 3.6)
project(document_similarity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(jaccard src/jaccard-similarity/main.cpp)
add_executable(jaccard-minhash src/jaccard-minhash/main.cpp)
add_executable(lsh-minhash src/lsh-minhash/main.cpp)

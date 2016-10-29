cmake_minimum_required(VERSION 3.6)
project(document_similarity)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(document_similarity main.cpp)
add_executable(jaccard-similarity jaccard-similarity/main.cpp)
cmake_minimum_required(VERSION 3.6)
project(document_similarity)

find_package(Boost 1.62.0 COMPONENTS system filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB classes
        "src/classes/*.hpp"
        "src/classes/*.cpp"
        )

add_executable(comparator src/main.cpp ${classes})
target_link_libraries(comparator ${Boost_LIBRARIES})
cmake_minimum_required(VERSION 3.6)
project(document_similarity)

find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

file(GLOB classes
        "src/classes/*.hpp"
        "src/classes/*.cpp"
        )

add_executable(comparator src/main.cpp ${classes} src/prova.cpp)
target_link_libraries(comparator ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
add_executable(prova src/prova.cpp ${classes})
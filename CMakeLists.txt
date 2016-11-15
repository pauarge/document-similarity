cmake_minimum_required(VERSION 3.6)
project(document_similarity)

find_package(Boost COMPONENTS system filesystem REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB classes "src/classes/*.hpp" "src/classes/*.cpp")
file(GLOB utils "src/utils/*.hpp" "src/utils/*.cpp")

add_executable(comparator src/main.cpp ${classes} ${utils})
add_executable(experiments src/mainExperiments.cpp ${classes} ${utils})
target_link_libraries(comparator ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
target_link_libraries(experiments ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
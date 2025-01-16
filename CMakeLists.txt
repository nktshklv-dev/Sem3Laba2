cmake_minimum_required(VERSION 3.28)
project(Laba2)

set(CMAKE_CXX_STANDARD 17)

set(Python3_EXECUTABLE "/Users/nick/Documents/Labs/Sem3/Laba2/venv/bin/python3")

find_package(Python3 REQUIRED COMPONENTS Development)

include_directories("/Users/nick/Documents/Labs/Sem3/Laba2/venv/include/python3.13")

include_directories("/Users/nick/Documents/Labs/Sem3/Laba2/venv/lib/python3.13/site-packages/numpy/_core/include")

add_subdirectory(third_party/FTXUI)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")
endif()

add_executable(Laba2 main.cpp
        ISequence.h
        DynamicArray.h
        ISorter.h
        InsertionSorter.h
        MergeSorter.h
        HeapSorter.h
        Person.h
        NameDatabase.h
        DataGenerator.h
)

target_include_directories(Laba2 PRIVATE ${Python3_INCLUDE_DIRS} third_party/matplotlib-cpp)
target_link_libraries(Laba2 PRIVATE ftxui::screen ftxui::dom ftxui::component ${Python3_LIBRARIES})
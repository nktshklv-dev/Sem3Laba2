cmake_minimum_required(VERSION 3.28)
project(Laba2)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(third_party/FTXUI)

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

target_link_libraries(Laba2 PRIVATE ftxui::screen ftxui::dom ftxui::component)

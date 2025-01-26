#ifndef PERFORMANCETESTS_H
#define PERFORMANCETESTS_H
#include <iostream>
#include "DynamicArray.h"
#include "InsertionSorter.h"
#include "Person.h"

template<typename T>
void measureSortingTime(DynamicArray<T>* array, ISorter<T>& sorter, SortBy sortBy) {
    auto start = std::chrono::high_resolution_clock::now();

    sorter.Sort(array, sortBy);

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Время выполнения: " << duration.count() << " мс\n";
}

void runPerformanceTests() {
    std::cout << "Запуск нагрузочных тестов...\n";
    std::vector<int> sizes = {1000, 5000, 10000};

    for (int size : sizes) {
        std::cout << "Тестирование на " << size << " элементах:\n";

        DynamicArray<Person> persons;
        for (int i = 0; i < size; ++i) {
            persons.Append(Person());
        }

        {
            DynamicArray<Person> copy = persons;
            InsertionSorter<Person> sorter;
            std::cout << "Insertion Sort: ";
            measureSortingTime(&copy, sorter, SortBy::SSN);
        }

        {
            DynamicArray<Person> copy = persons;
            MergeSorter<Person> sorter;
            std::cout << "Merge Sort: ";
            measureSortingTime(&copy, sorter, SortBy::SSN);
        }

        {
            DynamicArray<Person> copy = persons;
            HeapSorter<Person> sorter;
            std::cout << "Heap Sort: ";
            measureSortingTime(&copy, sorter, SortBy::SSN);
        }

        std::cout << "------------------------\n";
    }
    std::cout << "Нагрузочные тесты завершены.\n";
}

#endif //PERFORMANCETESTS_H


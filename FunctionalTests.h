#ifndef FUNCTIONALTESTS_H
#define FUNCTIONALTESTS_H

#include <cassert>
#include <iostream>
#include "DynamicArray.h"
#include "InsertionSorter.h"
#include "MergeSorter.h"
#include "HeapSorter.h"
#include "Person.h"
#include "SortBy.h"

void testSortingAlgorithms() {
    std::cout << "Запуск функциональных тестов для алгоритмов сортировки...\n";

    DynamicArray<Person> persons;
    for (int i = 0; i < 1000; ++i) {
        persons.Append(Person());
    }

    {
        DynamicArray<Person> copy = persons;
        InsertionSorter<Person> sorter;
        sorter.Sort(&copy, SortBy::SSN);

        for (int i = 1; i < copy.GetLength(); ++i) {
            assert(copy.GetElement(i - 1).getSSN() <= copy.GetElement(i).getSSN());
        }
        std::cout << "Insertion Sort: Тест пройден!\n";
    }


    {
        DynamicArray<Person> copy = persons;
        MergeSorter<Person> sorter;
        sorter.Sort(&copy, SortBy::SSN);

        for (int i = 1; i < copy.GetLength(); ++i) {
            assert(copy.GetElement(i - 1).getSSN() <= copy.GetElement(i).getSSN());
        }
        std::cout << "Merge Sort: Тест пройден!\n";
    }

    {
        DynamicArray<Person> copy = persons;
        HeapSorter<Person> sorter;
        sorter.Sort(&copy, SortBy::SSN);

        for (int i = 1; i < copy.GetLength(); ++i) {
            assert(copy.GetElement(i - 1).getSSN() <= copy.GetElement(i).getSSN());
        }
        std::cout << "Heap Sort: Тест пройден!\n";
    }
}
void testDynamicArray() {
    std::cout << "Запуск функциональных тестов для DynamicArray...\n";

    {
        DynamicArray<int> arr(5);
        for (int i = 0; i < 5; ++i) {
            arr.Set(i, i * 10);
        }

        assert(arr.GetLength() == 5);
        for (int i = 0; i < 5; ++i) {
            assert(arr.GetElement(i) == i * 10);
        }
        std::cout << "Тест для GetLength() и GetElement() успешно пройден\n";
    }

    {
        DynamicArray<int> arr;
        arr.Append(10);
        arr.Append(20);
        arr.Prepend(5);
        arr.InsertAt(15, 2);

        assert(arr.GetLength() == 4);
        assert(arr.GetElement(0) == 5);
        assert(arr.GetElement(1) == 10);
        assert(arr.GetElement(2) == 15);
        assert(arr.GetElement(3) == 20);
        std::cout << "Тест для Append(), Prepend(), InsertAt() успешно пройден. \n";
    }

    {
        DynamicArray<int> arr;
        for (int i = 0; i < 10; ++i) {
            arr.Append(i * 10);
        }

        ISequence<int>* subSeq = arr.GetSubSequence(2, 5);
        assert(subSeq->GetLength() == 4);
        assert(subSeq->GetElement(0) == 20);
        assert(subSeq->GetElement(1) == 30);
        assert(subSeq->GetElement(2) == 40);
        assert(subSeq->GetElement(3) == 50);

        delete subSeq;
        std::cout << "Тест для GetSubsequence() успешно пройден.\n";
    }

    {
        DynamicArray<int> arr;
        arr.Append(10);
        arr.Append(20);
        arr.Swap(arr[0], arr[1]);

        assert(arr.GetElement(0) == 20);
        assert(arr.GetElement(1) == 10);
        std::cout << "Тест для Swap() успешно пройден.\n";
    }

    {
        DynamicArray<int> arr;
        arr.Append(10);
        arr.Append(20);
        arr.Append(30);

        assert(arr.GetFirstElement() == 10);
        assert(arr.GetLastElement() == 30);
        std::cout << "Тест GetFirstElement() и GetLastElement успешно пройден.\n";
    }

    std::cout << "Все функциональные тесты для DynamicArray пройдены успешно!\n";
}

void runFunctionalTests() {
    std::cout << "Запуск функциональных тестов...\n";

    testDynamicArray();
    testSortingAlgorithms();

    std::cout << "Функциональные тесты завершены.\n";
}
#endif //FUNCTIONALTESTS_H

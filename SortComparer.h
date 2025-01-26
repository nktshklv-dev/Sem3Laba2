#include <fstream>
#include <sstream>
#include <vector>
#include "DynamicArray.h"
#include "InsertionSorter.h"
#include "MergeSorter.h"
#include "HeapSorter.h"
#include "Person.h"
#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

void loadDataFromFile(const std::string& fileName, DynamicArray<Person>& persons, int data_size) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("ошибка при открытии файла");
    }

    std::string line;
    int count = 0;
    while (std::getline(file, line) && count < data_size) {
        std::stringstream ss(line);
        std::string firstName, lastName, middleName;
        int yearOfBirth, SSN;
        double heightInMeters;
        char comma;

        ss >> firstName >> comma
           >> lastName >> comma
           >> middleName >> comma
           >> yearOfBirth >> comma
           >> SSN >> comma
           >> heightInMeters;

        persons.Append(Person(firstName, lastName, middleName, yearOfBirth, SSN, heightInMeters));
        count++;
    }
    file.close();
}

template <typename T>
double measureSortingTime(ISequence<T>* sequence, ISorter<T>& sorter) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.Sort(sequence);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void compareSortingAlgorithms(const DynamicArray<Person>* data, std::vector<double>& sizes, std::vector<double>& insertionTimes, std::vector<double>& mergeTimes, std::vector<double>& heapTimes) {
    InsertionSorter<Person> insertionSorter;
    MergeSorter<Person> mergeSorter;
    HeapSorter<Person> heapSorter;

    for (int size : sizes) {
        DynamicArray<Person> copy1 = *data;
        DynamicArray<Person> copy2 = *data;
        DynamicArray<Person> copy3 = *data;

        double insertionTime = measureSortingTime(&copy1, insertionSorter);
        double mergeTime = measureSortingTime(&copy2, mergeSorter);
        double heapTime = measureSortingTime(&copy3, heapSorter);

        insertionTimes.push_back(insertionTime);
        mergeTimes.push_back(mergeTime);
        heapTimes.push_back(heapTime);
    }
}

void buildGraph( std::vector<double>& sizes, std::vector<double>& insertionTimes, std::vector<double>& mergeTimes, std::vector<double>& heapTimes) {
    plt::figure();
    std::map<std::string, std::string> insertionParams = {{"label", "Insertion Sort"}};
    std::map<std::string, std::string> mergeParams = {{"label", "Merge Sort"}};
    std::map<std::string, std::string> heapParams = {{"label", "Heap Sort"}};

    plt::plot(sizes, insertionTimes, "r-");
    plt::plot(sizes, mergeTimes, "g-");
    plt::plot(sizes, heapTimes, "b-");

    plt::title("Сравнение сортировок");
    plt::xlabel("Количество объектов");
    plt::ylabel("Время");
    plt::legend();
    plt::grid(true);

    plt::save("graph.pdf");
    plt::show();
}

void compareDataAndBuildGraph(const DynamicArray<Person>& data) {
    std::vector<double> sizes = {10, 100, 1000, 5000, 10000, 20000, 30000, 60000, 80000, 100000};
    std::vector<double> insertionTimes;
    std::vector<double> mergeTimes;
    std::vector<double> heapTimes;

    if (data.GetLength() < sizes.back()) {
        throw std::runtime_error("Недостаточно данных для сравнения сортировок");
    }

    compareSortingAlgorithms(&data, sizes, insertionTimes, mergeTimes, heapTimes);
    buildGraph(sizes, insertionTimes, mergeTimes, heapTimes);
}



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

void loadDataFromFile(DynamicArray<Person>& persons, const std::string& fileName, int data_size) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    std::cout << "Загрузка данных из файла..." << std::endl;

    std::string line;
    int count = 0;
    while (std::getline(file, line) && count < data_size) {
        size_t pos1 = line.find(',');
        size_t pos2 = line.find(',', pos1 + 1);
        size_t pos3 = line.find(',', pos2 + 1);
        size_t pos4 = line.find(',', pos3 + 1);
        size_t pos5 = line.find(',', pos4 + 1);

        if (pos1 == std::string::npos || pos2 == std::string::npos || pos3 == std::string::npos ||
            pos4 == std::string::npos || pos5 == std::string::npos) {
            throw std::runtime_error("Некорректный формат данных в файле");
            }

        std::string firstName = line.substr(0, pos1);
        std::string lastName = line.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string middleName = line.substr(pos2 + 1, pos3 - pos2 - 1);
        int yearOfBirth = std::stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
        int SSN = std::stoi(line.substr(pos4 + 1, pos5 - pos4 - 1));
        double heightInMeters = std::stod(line.substr(pos5 + 1));

        persons.Append(Person(firstName, lastName, middleName, yearOfBirth, SSN, heightInMeters));
        count++;

        if (count % 5000 == 0) {
            std::cout << "Загружено " << count << " записей..." << std::endl;
        }
    }

    file.close();
    std::cout << "Загрузка завершена. Всего загружено " << count << " записей." << std::endl;
}
template <typename T>
double measureSortingTime(ISequence<T>* sequence, ISorter<T>& sorter, SortBy sortBy) {
    auto start = std::chrono::high_resolution_clock::now();
    sorter.Sort(sequence, sortBy);
    auto end = std::chrono::high_resolution_clock::now();

    return std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
}

void compareSortingAlgorithms(const DynamicArray<Person>& data, std::vector<double>& sizes, std::vector<double>& insertionTimes, std::vector<double>& mergeTimes, std::vector<double>& heapTimes, SortBy sortBy) {
    InsertionSorter<Person> insertionSorter;
    MergeSorter<Person> mergeSorter;
    HeapSorter<Person> heapSorter;

    for (int size : sizes) {
        std::cout << "Идет сравнение алгоритмов для " << size << " элементов" << std::endl;

        DynamicArray<Person> subset;
        for (int i = 0; i < size; ++i) {
            subset.Append(data[i]);
        }

        DynamicArray<Person> copy1 = subset;
        DynamicArray<Person> copy2 = subset;
        DynamicArray<Person> copy3 = subset;

        double insertionTime = measureSortingTime(&copy1, insertionSorter, sortBy);
        double mergeTime = measureSortingTime(&copy2, mergeSorter, sortBy);
        double heapTime = measureSortingTime(&copy3, heapSorter, sortBy);

        insertionTimes.push_back(insertionTime);
        mergeTimes.push_back(mergeTime);
        heapTimes.push_back(heapTime);
    }
}
void buildGraph(std::vector<double>& sizes, std::vector<double>& insertionTimes, std::vector<double>& mergeTimes, std::vector<double>& heapTimes) {
    plt::figure();

    plt::plot(sizes, insertionTimes, {{"label", "Insertion Sort"}, {"color", "red"}});
    plt::plot(sizes, mergeTimes, {{"label", "Merge Sort"}, {"color", "green"}});
    plt::plot(sizes, heapTimes, {{"label", "Heap Sort"}, {"color", "blue"}});

    plt::title("Сравнение сортировок");
    plt::xlabel("Количество объектов");

    plt::ylabel("Время (мс)");
    plt::legend();
    plt::grid(true);

    plt::save("graph.pdf");
    plt::show();
}

void compareDataAndBuildGraph(const DynamicArray<Person>& data, SortBy sortBy) {
    int totalDataSize = data.GetLength();
    int numberOfSections = 10;
    std::vector<double> sizes;
    std::vector<double> insertionTimes;
    std::vector<double> mergeTimes;
    std::vector<double> heapTimes;

    for (int i = 1; i <= numberOfSections; ++i) {
        sizes.push_back((totalDataSize * i) / numberOfSections);
    }

    compareSortingAlgorithms(data, sizes, insertionTimes, mergeTimes, heapTimes, sortBy);

    buildGraph(sizes, insertionTimes, mergeTimes, heapTimes);
}

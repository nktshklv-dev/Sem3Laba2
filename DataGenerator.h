#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <fstream>
#include <string>
#include <algorithm> // Для std::sort
#include <vector>    // Для std::vector
#include "Person.h"
#include "DynamicArray.h"

void createUnsortedDataFile(const std::string& fileName, int data_size = 100000) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    for (int i = 0; i < data_size; ++i) {
        Person person;
        file << person.getFirstName() << ","
             << person.getLastName() << ","
             << person.getMiddleName() << ","
             << person.getYearOfBirth() << ","
             << person.getSSN() << ","
             << person.getHeightInMeters() << "\n";
    }
    file.close();
}

void createSortedDataFile(const std::string& fileName, int data_size = 100000) {
    DynamicArray<Person> persons(data_size);

    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, Person());
    }

    // Копируем данные в std::vector для сортировки
    std::vector<Person> temp(data_size);
    for (int i = 0; i < data_size; ++i) {
        temp[i] = persons.GetElement(i);
    }

    // Сортируем std::vector
    std::sort(temp.begin(), temp.end(), [](const Person& a, const Person& b) {
        return a.getSSN() < b.getSSN();
    });

    // Копируем отсортированные данные обратно в DynamicArray
    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, temp[i]);
    }

    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    for (int i = 0; i < data_size; ++i) {
        Person person = persons.GetElement(i);
        file << person.getFirstName() << ","
             << person.getLastName() << ","
             << person.getMiddleName() << ","
             << person.getYearOfBirth() << ","
             << person.getSSN() << ","
             << person.getHeightInMeters() << "\n";
    }
    file.close();
}

void createReverseSortedDataFile(const std::string& fileName, int data_size = 100000) {
    DynamicArray<Person> persons(data_size);

    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, Person());
    }

    // Копируем данные в std::vector для сортировки
    std::vector<Person> temp(data_size);
    for (int i = 0; i < data_size; ++i) {
        temp[i] = persons.GetElement(i);
    }

    // Сортируем std::vector в обратном порядке
    std::sort(temp.begin(), temp.end(), [](const Person& a, const Person& b) {
        return a.getSSN() > b.getSSN();
    });

    // Копируем отсортированные данные обратно в DynamicArray
    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, temp[i]);
    }

    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    for (int i = 0; i < data_size; ++i) {
        Person person = persons.GetElement(i);
        file << person.getFirstName() << ","
             << person.getLastName() << ","
             << person.getMiddleName() << ","
             << person.getYearOfBirth() << ","
             << person.getSSN() << ","
             << person.getHeightInMeters() << "\n";
    }
    file.close();
}

#endif // DATAGENERATOR_H
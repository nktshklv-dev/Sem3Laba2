#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
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

    std::vector<Person> temp(data_size);
    for (int i = 0; i < data_size; ++i) {
        temp[i] = persons.GetElement(i);
    }

    std::sort(temp.begin(), temp.end(), [](const Person& a, const Person& b) {
        return a.getSSN() < b.getSSN();
    });

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

    std::vector<Person> temp(data_size);
    for (int i = 0; i < data_size; ++i) {
        temp[i] = persons.GetElement(i);
    }

    std::sort(temp.begin(), temp.end(), [](const Person& a, const Person& b) {
        return a.getSSN() > b.getSSN();
    });

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

DynamicArray<Person> loadDataFromFile(const std::string& fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    DynamicArray<Person> persons;
    std::string line;
    while (std::getline(file, line)) {
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
    }

    file.close();
    return persons;
}

#endif // DATAGENERATOR_H
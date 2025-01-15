#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <fstream>
#include <string>
#include <algorithm>
#include "Person.h"
#include "DynamicArray.h"

// Создание файла с неотсортированными данными
void createUnsortedDataFile(const std::string& fileName, int data_size = 100000) {
    std::ofstream file(fileName);

    if (!file.is_open()) {
        throw std::runtime_error("Ошибка при открытии файла");
    }

    for (int i = 0; i < data_size; ++i) {
        Person person;  // Создаем случайный объект Person
        file << person.getFirstName() << ","
             << person.getLastName() << ","
             << person.getMiddleName() << ","
             << person.getYearOfBirth() << ","
             << person.getSSN() << ","
             << person.getHeightInMeters() << "\n";
    }
    file.close();
}

// Создание файла с отсортированными данными
void createSortedDataFile(const std::string& fileName, int data_size = 100000) {
    DynamicArray<Person> persons(data_size);

    // Заполняем массив случайными объектами Person
    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, Person());
    }

    // Сортируем массив по SSN (социальный номер)
    for (int i = 0; i < data_size - 1; ++i) {
        for (int j = 0; j < data_size - i - 1; ++j) {
            if (persons.GetElement(j).getSSN() > persons.GetElement(j + 1).getSSN()) {
                Person temp = persons.GetElement(j);
                persons.Set(j, persons.GetElement(j + 1));
                persons.Set(j + 1, temp);
            }
        }
    }

    // Записываем отсортированные данные в файл
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

// Создание файла с обратно отсортированными данными
void createReverseSortedDataFile(const std::string& fileName, int data_size = 100000) {
    DynamicArray<Person> persons(data_size);

    // Заполняем массив случайными объектами Person
    for (int i = 0; i < data_size; ++i) {
        persons.Set(i, Person());
    }

    // Сортируем массив по SSN в обратном порядке
    for (int i = 0; i < data_size - 1; ++i) {
        for (int j = 0; j < data_size - i - 1; ++j) {
            if (persons.GetElement(j).getSSN() < persons.GetElement(j + 1).getSSN()) {
                Person temp = persons.GetElement(j);
                persons.Set(j, persons.GetElement(j + 1));
                persons.Set(j + 1, temp);
            }
        }
    }

    // Записываем обратно отсортированные данные в файл
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
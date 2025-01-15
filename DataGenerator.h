
#ifndef DATAGENERATOR_H
#define DATAGENERATOR_H

#include <fstream>
#include <string>
#include "Person.h"

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

void createSortedDataFile(const std::string& fileName, int data_size = 100000) {

}


#endif //DATAGENERATOR_H

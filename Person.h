#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <cstdlib>
#include <random>
#include "NameDatabase.h"

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::string middleName;
    int yearOfBirth;
    int socialSecurityNumber;
    double heightInMeters;

     
    static std::default_random_engine randomEngine;
    static std::uniform_int_distribution<int> yearDistribution;
    static std::uniform_real_distribution<double> heightDistribution;
    static std::uniform_int_distribution<int> ssnDistribution;

    int generateRandomYearOfBirth() {
        return yearDistribution(randomEngine);
    }

    double generateRandomHeightInMeters() {
        return heightDistribution(randomEngine);
    }

    int generateRandomSSN() {
        return ssnDistribution(randomEngine);
    }

public:
    Person() {
        firstName = firstNameStorage[rand() % firstNameCount];
        lastName = lastNameStorage[rand() % lastNameCount];
        middleName = middleNameStorage[rand() % middleNameCount];
        yearOfBirth = generateRandomYearOfBirth();
        socialSecurityNumber = generateRandomSSN();
        heightInMeters = generateRandomHeightInMeters();
    }

    Person(std::string firstName, std::string lastName, std::string middleName, int yearOfBirth, int SSN, double heightInMeters) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->middleName = middleName;
        this->yearOfBirth = yearOfBirth;
        this->socialSecurityNumber = SSN;
        this->heightInMeters = heightInMeters;
    }

    std::string getFirstName() const {
        return firstName;
    }

    std::string getLastName() const {
        return lastName;
    }

    std::string getMiddleName() const {
        return middleName;
    }

    int getYearOfBirth() const {
        return yearOfBirth;
    }

    int getSSN() const {
        return socialSecurityNumber;
    }

    double getHeightInMeters() const {
        return heightInMeters;
    }
};

std::default_random_engine Person::randomEngine(std::random_device{}());
std::uniform_int_distribution<int> Person::yearDistribution(1950, 2024);
std::uniform_real_distribution<double> Person::heightDistribution(1.50, 2.00);
std::uniform_int_distribution<int> Person::ssnDistribution(100000000, 999999999);

#endif // PERSON_H
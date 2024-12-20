#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <cstblib>
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


    int generateRandomYearOfBirth() {
        int loweBound = 1950;
        int upperBound = 2024;
        std::uniform_int_distribution<int> unif(loweBound, upperBound);
        std::default_random_engine re;
        int randomYear = unif(re);
        return randomYear;
    }

    double generateRandomHeightInMeters() {
        double lowerBound = 1.50;
        double upperBound = 2.00;
        std::uniform_real_distribution<double> unif(lowerBound, upperBound);
        std::default_random_engine re;
        double randomHeightInMeters = unif(re);
        return randomHeightInMeters;
    }

    int generateRandomSSN() {
        int lowerBound = 100000000;
        int upperBound = 999999999;
        std::uniform_real_distribution<int> unif(lowerBound, upperBound);
        std::default_random_engine re;
        int randomSSN = unif(re);
        return randomSSN;
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

    bool operator < (const Person& other) const {
        return socialSecurityNumber < other.socialSecurityNumber;
    }

    bool operator > (const Person& other) const {
        return socialSecurityNumber > other.socialSecurityNumber;
    }

    bool operator <= (const Person& other) const {
        return socialSecurityNumber <= other.socialSecurityNumber;
    }

    bool operator >= (const Person& other) const {
        return socialSecurityNumber >= other.socialSecurityNumber;
    }

    bool operator == (const Person& other) const {
        return socialSecurityNumber == other.socialSecurityNumber;
    }

    bool operator != (const Person& other) const {
        return socialSecurityNumber != other.socialSecurityNumber;
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

#endif //PERSON_H

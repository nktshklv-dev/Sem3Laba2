
#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <string>
#include <fstream>
#include "DataGenerator.h"
#include "SortComparer.h"
#include <atomic>
#include <thread>
#include <limits>

#include "FunctionalTests.h"
#include "PerformanceTests.h"

int getValidatedInput() {
    int value;
    while (true) {
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Некорректный ввод. Пожалуйста, введите число: ";
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

void showMainMenu() {
    std::cout << "Главное меню:\n";
    std::cout << "1. Сравнить алгоритмы сортировки\n";
    std::cout << "2. Запустить тесты\n";
    std::cout << "3. Выход\n";
}

void showDataTypeMenu() {
    std::cout << "Выберите формат данных:\n";
    std::cout << "1. Отсортированные данные\n";
    std::cout << "2. Обратно отсортированные данные\n";
    std::cout << "3. Случайные данные\n";
    std::cout << "4. Назад\n";
}

void loadingIndicator(std::atomic<bool>& isLoading) {
    std::cout << "Файл с данными создается";
    std::cout.flush();

    while (isLoading) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << ".";
        std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\n";
    std::cout << "Файл с данными создан!" << std::endl;
}

int getDataSizeFromUser() {
    int dataSize;
    std::cout << "Введите количество данных (например, 1000, 10000, 100000): ";
    dataSize = getValidatedInput();

    if (dataSize <= 0) {
        throw std::invalid_argument("Количество данных должно быть положительным числом.");
    }

    return dataSize;
}

void showSortByMenu() {
    std::cout << "Выберите поле для сортировки:\n";
    std::cout << "1. По SSN (номер социального страхования)\n";
    std::cout << "2. По имени\n";
    std::cout << "3. По фамилии\n";
    std::cout << "4. По году рождения\n";
    std::cout << "5. По росту\n";
    std::cout << "6. Назад\n";
}

SortBy getSortByFromUser() {
    int choice;
    while (true) {
        showSortByMenu();
        choice = getValidatedInput();

        switch (choice) {
            case 1:
                return SortBy::SSN;
            case 2:
                return SortBy::FirstName;
            case 3:
                return SortBy::LastName;
            case 4:
                return SortBy::YearOfBirth;
            case 5:
                return SortBy::Height;
            case 6:
                throw std::runtime_error("Возврат в предыдущее меню.");
            default:
                std::cout << "Неверный выбор. Попробуйте снова.\n";
            break;
        }
    }
}

void showTestMenu() {
    std::cout << "Выберите тип тестов:\n";
    std::cout << "1. Функциональные тесты\n";
    std::cout << "2. Нагрузочные тесты\n";
    std::cout << "3. Назад\n";
}

void openMenu() {
     int selectedMainMenu = 0;
    int selectedDataType = 0;
    int selectedTestType = 0;

    while (true) {
        showMainMenu();
        selectedMainMenu = getValidatedInput();

        if (selectedMainMenu == 1) {
            while (true) {
                showDataTypeMenu();
                selectedDataType = getValidatedInput();

                try {
                    int dataSize = getDataSizeFromUser();
                    if (selectedDataType == 1) {
                        std::atomic isLoading(true);
                        std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                        createSortedDataFile("sorted_data.txt", dataSize);
                        isLoading = false;
                        loadingThread.join();
                        DynamicArray<Person> persons;
                        loadDataFromFile(persons, "sorted_data.txt", dataSize);
                        SortBy sortBy = getSortByFromUser();
                        compareDataAndBuildGraph(persons, sortBy);
                    } else if (selectedDataType == 2) {
                        std::atomic isLoading(true);
                        std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                        createReverseSortedDataFile("reverse_sorted_data.txt", dataSize);
                        isLoading = false;
                        loadingThread.join();
                        DynamicArray<Person> persons;
                        loadDataFromFile(persons, "reverse_sorted_data.txt", dataSize);
                        SortBy sortBy = getSortByFromUser();
                        compareDataAndBuildGraph(persons, sortBy);
                    } else if (selectedDataType == 3) {
                        std::atomic isLoading(true);
                        std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                        createUnsortedDataFile("random_data.txt", dataSize);
                        isLoading = false;
                        loadingThread.join();
                        DynamicArray<Person> persons;
                        loadDataFromFile(persons, "random_data.txt", dataSize);
                        SortBy sortBy = getSortByFromUser();
                        compareDataAndBuildGraph(persons, sortBy);
                    } else if (selectedDataType == 4) {
                        break;
                    } else {
                        std::cout << "Неверный выбор. Попробуйте снова.\n";
                    }
                } catch (const std::exception& e) {
                    std::cerr << "Ошибка: " << e.what() << std::endl;
                }
            }
        } else if (selectedMainMenu == 2) {
                while(true) {
                    showTestMenu();
                    selectedTestType = getValidatedInput();
                    try {
                        if (selectedTestType == 1) {
                            runFunctionalTests();
                        } else if (selectedTestType == 2) {
                            runPerformanceTests();
                        } else if (selectedTestType == 3) {
                            break;
                        } else {
                            std::cout << "Неверный выбор. Попробуйте снова.\n";
                        }
                    } catch (const std::exception& e) {
                        std::cerr << "Ошибка: " << e.what() << std::endl;
                    }

                }
        } else if (selectedMainMenu == 3) {
            break;
        } else {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

}


#endif //MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include "DataGenerator.h"
#include "SortComparer.h"
#include <atomic>
#include <thread>

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
    std::cout << "Данные создаются";
    std::cout.flush();

    while (isLoading) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << ".";
        std::cout.flush();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    std::cout << "\n";
    std::cout << "Данные созданы!" << std::endl;
}


int main() {
    int selectedMainMenu = 0;
    int selectedDataType = 0;

    while (true) {
        showMainMenu();
        std::cin >> selectedMainMenu;

        if (selectedMainMenu == 1) {
            while (true) {
                showDataTypeMenu();
                std::cin >> selectedDataType;

                if (selectedDataType == 1) {
                    std::atomic isLoading(true);
                    std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                    createSortedDataFile("sorted_data.txt");
                    isLoading = false;
                    loadingThread.join();
                    DynamicArray<Person> sortedData = loadDataFromFile("sorted_data.txt", 100000);
                    compareDataAndBuildGraph(sortedData);
                } else if (selectedDataType == 2) {
                    std::atomic isLoading(true);
                    std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                    createReverseSortedDataFile("reverse_sorted_data.txt");
                    isLoading = false;
                    loadingThread.join();
                } else if (selectedDataType == 3) {
                    std::atomic isLoading(true);
                    std::thread loadingThread(loadingIndicator, std::ref(isLoading));
                    createUnsortedDataFile("random_data.txt");
                    isLoading = false;
                    loadingThread.join();
                } else if (selectedDataType == 4) {
                    break;
                } else {
                    std::cout << "Неверный выбор. Попробуйте снова.\n";
                }
            }
        } else if (selectedMainMenu == 2) {

            std::cout << "Тесты запущены.\n";
        } else if (selectedMainMenu == 3) {
            break;
        } else {
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    }

    return 0;
}
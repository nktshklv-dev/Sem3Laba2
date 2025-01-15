#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <thread>
#include <chrono>
#include "DataGenerator.h"

using namespace ftxui;

// Функция для генерации случайных чисел
int generateRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    return distrib(gen);
}

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected_main_menu = 0;
    int selected_data_type = 0;
    std::string filename;  // Имя файла для неотсортированных данных
    bool loading = false;  // Состояние загрузки
    int spinner_frame = 0;  // Кадр анимации спиннера

    std::vector<std::string> main_menu_entries = {
        "1. Сравнить алгоритмы сортировки",
        "2. Запустить тесты",
        "Выход"
    };

    auto main_menu = Menu(&main_menu_entries, &selected_main_menu);

    std::vector<std::string> data_type_entries = {
        "1. Отсортированные данные",
        "2. Обратно отсортированные данные",
        "3. Случайные данные",
        "Назад"
    };

    auto data_type_menu = Menu(&data_type_entries, &selected_data_type);

    // Компонент для отображения индикатора загрузки
    auto loading_indicator = Renderer([&] {
        if (loading) {
            return hbox({
                text("Данные создаются") | bold,
                text(" "),  // Просто пробел для разделения
                spinner(2, spinner_frame)  // Вращающийся индикатор
            }) | center;  // Убрали border
        } else {
            return text("");  // Пустой элемент, если загрузка не активна
        }
    });

    auto data_type_renderer = Renderer(data_type_menu, [&]{
        return vbox ({
            text("Выберите формат данных") | center | bold | color(Color::Blue),
            separator(),
            data_type_menu->Render(),
            separator(),
            loading_indicator->Render()  // Добавляем индикатор загрузки
        }) | border | center;
    });

    // Обработчик событий для data_type_renderer
    auto data_type_component = CatchEvent(data_type_renderer, [&](Event event) {
        if (event == Event::Return) {
            switch (selected_data_type) {
                case 0:  // Отсортированные данные
                case 1:  // Обратно отсортированные данные
                case 2: {  // Случайные данные
                    loading = true;
                    spinner_frame = 0;

                    // Запуск асинхронной задачи для имитации загрузки
                    std::thread([&] {
                        for (int i = 0; i < 30; ++i) {  // 30 шагов по 100 мс = 3 секунды
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                            spinner_frame++;  // Обновляем кадр спиннера
                            screen.PostEvent(Event::Custom);  // Обновляем экран
                        }
                        loading = false;
                        screen.PostEvent(Event::Custom);  // Обновляем экран
                    }).detach();
                    break;
                }
                case 3:  // Назад
                    screen.Exit();
                    break;
            }
            return true;
        }
        return false;
    });

    auto main_component = CatchEvent(main_menu, [&](Event event) {
        if (event == Event::Return) {
            switch (selected_main_menu) {
                case 0:
                    screen.Loop(data_type_component);
                    break;
                case 1:
                    // Запуск тестов
                    break;
                case 2:
                    screen.Exit();
                    break;
            }
            return true;
        }
        return false;
    });

    // Компоновка интерфейса
    auto layout = Container::Vertical({
        main_component
    });

    auto renderer = Renderer(layout, [&] {
        return vbox({
            text("Главное меню") | center | bold | color(Color::Blue),
            separator(),
            main_component->Render(),
            separator()
        }) | border | center;
    });

    screen.Loop(renderer);

    return 0;
}
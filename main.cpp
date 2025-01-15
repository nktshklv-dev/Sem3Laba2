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

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected_main_menu = 0;
    int selected_data_type = 0;
    bool loading = false;
    int spinner_frame = 0;

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

    auto loading_indicator = Renderer([&] {
        if (loading) {
            return hbox({
                text("Данные создаются") | bold,
                text(" "),
                spinner(2, spinner_frame)
            }) | center;
        } else {
            return text("");
        }
    });

    auto data_type_renderer = Renderer(data_type_menu, [&] {
        return vbox({
            text("Выберите формат данных") | center | bold | color(Color::Blue),
            separator(),
            data_type_menu->Render(),
            separator(),
            loading_indicator->Render()
        }) | border | center;
    });

    auto data_type_component = CatchEvent(data_type_renderer, [&](Event event) {
        if (event == Event::Return) {
            switch (selected_data_type) {
                case 0:
                    loading = true;
                    spinner_frame = 0;

                    std::thread([&] {
                        auto start_time = std::chrono::steady_clock::now();

                        while (std::chrono::duration_cast<std::chrono::seconds>(
                                   std::chrono::steady_clock::now() - start_time).count() < 23) {
                            spinner_frame++;
                            screen.PostEvent(Event::Custom);
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }

                        createSortedDataFile("sorted_data.txt");
                        loading = false;
                        screen.PostEvent(Event::Custom);
                    }).detach();
                    break;

                case 1:
                    loading = true;
                    spinner_frame = 0;

                    std::thread([&] {
                        auto start_time = std::chrono::steady_clock::now();

                        while (std::chrono::duration_cast<std::chrono::seconds>(
                                   std::chrono::steady_clock::now() - start_time).count() < 23) {
                            spinner_frame++;
                            screen.PostEvent(Event::Custom);
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }

                        createReverseSortedDataFile("reverse_sorted_data.txt");
                        loading = false;
                        screen.PostEvent(Event::Custom);
                    }).detach();
                    break;

                case 2:
                    loading = true;
                    spinner_frame = 0;

                    std::thread([&] {
                        auto start_time = std::chrono::steady_clock::now();

                        while (std::chrono::duration_cast<std::chrono::seconds>(
                                   std::chrono::steady_clock::now() - start_time).count() < 5) {
                            spinner_frame++;
                            screen.PostEvent(Event::Custom);
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                        }

                        createUnsortedDataFile("random_data.txt");
                        loading = false;
                        screen.PostEvent(Event::Custom);
                    }).detach();
                    break;

                case 3:
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
                    break;
                case 2:
                    screen.Exit();
                    break;
            }
            return true;
        }
        return false;
    });

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
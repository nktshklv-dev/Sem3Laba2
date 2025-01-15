#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace ftxui;

int main() {
    auto screen = ScreenInteractive::Fullscreen();

    int selected_main_menu = 0;
    std::string status_message;


    std::vector<std::string> main_menu_entries = {
        "1. Выбрать сортировку",
        "2. Создать данные",
        "3. Сравнить алгоритмы сортировки",
        "4. Запустить тесты",
        "Выход"
    };

    auto main_menu = Menu(&main_menu_entries, &selected_main_menu);

    auto main_component = CatchEvent(main_menu, [&](Event event) {
        if (event == Event::Return) {
            switch (selected_main_menu) {
                case 0:
                    status_message = "Выбрана сортировка!";
                    break;
                case 1:
                    status_message = "Данные созданы!";
                    break;
                case 2:
                    status_message = "Сравнение алгоритмов...";
                    break;
                case 3:
                    status_message = "Тесты запущены!";
                    break;
                case 4:
                    screen.Exit();
                    break;
                default:
                    status_message = "Неверный выбор!";
            }
            return true;
        }
        return false;
    });

    auto result_component = Renderer([&] {
        return text(status_message) | center | bold | color(Color::Green);
    });

    auto layout = Container::Vertical({
        main_component
    });

    auto renderer = Renderer(layout, [&] {
        return vbox({
            text("Главное меню") | center | bold | color(Color::Blue),
            separator(),
            main_component->Render(),
            separator(),
            result_component->Render()
        }) | border | center;
    });

    screen.Loop(renderer);

    return 0;
}
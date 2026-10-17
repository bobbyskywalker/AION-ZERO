#include "display/display.hpp"
#include "application/application.hpp"
#include "application/games/ashforged_blade/Module_ASH.hpp"
#include "application/main_menu/main_menu.hpp"

[[noreturn]] int main() {
    static auto lcd = display::LcdDisplay(VERTICAL);
    static auto app = Application(lcd);

    while (true) {
        switch (app.getCurrentModule().loop()) {
            case ModuleSwitchRequest::AshforgedBlade:
                app.switchModule<Module_ASH>(lcd);
                break;
            case ModuleSwitchRequest::MainMenu:
                app.switchModule<MainMenu>(lcd);
                break;
        }
        sleep_ms(16);
    }
}

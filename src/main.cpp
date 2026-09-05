#include "display/display.hpp"
#include "application/application.hpp"

[[noreturn]] int main() {
    static auto lcd = display::LcdDisplay(VERTICAL);
    static auto app = Application(lcd);

    while (true) {
        app.getCurrentModule().loop();
        sleep_ms(16);
    }
}
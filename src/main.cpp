#include "display/display.hpp"
#include "application/application.hpp"

int main() {
    static auto lcd = display::LcdDisplay(VERTICAL);
    static auto app = Application(lcd);

    app.getCurrentModule().loop();
    return 1;
}
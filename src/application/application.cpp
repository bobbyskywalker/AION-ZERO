#include "application.hpp"
#include "main_menu/main_menu.hpp"

Application::Application(display::LcdDisplay &display) : display_(display) {
    InputEngine::registerButtons();
    currentModule_ = std::make_unique<MainMenu>(display);
}

template<typename T>
void Application::switchModule() {
    currentModule_ = std::make_unique<T>();
}

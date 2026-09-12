#ifndef AION_ZERO_FMW_APPLICATION_HPP
#define AION_ZERO_FMW_APPLICATION_HPP

#include "module.hpp"
#include "../engine/input.hpp"
#include <memory>

class Application {
private:
    display::LcdDisplay& display_;
    std::unique_ptr<Module> currentModule_;;

public:
    explicit Application(display::LcdDisplay& display);
    ~Application() = default;

    template<typename T, typename... Args>
    void switchModule(Args&&... args);

    [[nodiscard]] Module& getCurrentModule() const { return *currentModule_; }
};

template<typename T, typename... Args>
void Application::switchModule(Args&&... args) {
    currentModule_ =
        std::make_unique<T>(std::forward<Args>(args)...);
}

#endif //AION_ZERO_FMW_APPLICATION_HPP
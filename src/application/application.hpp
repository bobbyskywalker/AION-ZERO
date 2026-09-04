#ifndef AION_ZERO_FMW_APPLICATION_HPP
#define AION_ZERO_FMW_APPLICATION_HPP

#include "module.hpp"
#include <memory>

class Application {
private:
    display::LcdDisplay& display_;
    std::unique_ptr<Module> currentModule_;;

public:
    explicit Application(display::LcdDisplay& display);
    ~Application() = default;

    template<typename T>
    void switchModule();

    [[nodiscard]] Module& getCurrentModule() const { return *currentModule_; }
};

#endif //AION_ZERO_FMW_APPLICATION_HPP
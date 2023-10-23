#include "application.h"

void Application::Config() {
    std::cout << "Config!\n";
}

void Application::Start(int argc, char **argv) {
    for (size_t i = 0; i < argc; ++i) {
        std::cout << argv[i] << std::endl;
    }
}
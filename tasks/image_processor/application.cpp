#include "application.h"

#include "crop_filter.h"

void Application::Config() {
    f_factory_.AddProducer("crop", ProduceCropFilter);
}

void Application::Start(int argc, char** argv) {
    try {
        cl_parser_.Parse(argc, argv, app_settings_);
        
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }
}
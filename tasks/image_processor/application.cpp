#include "application.h"
#include "sharpening_filter.h"

void Application::Config() {
    f_factory_.AddProducer("crop", ProduceCropFilter);
    f_factory_.AddProducer("gs", ProduceGrayscaleFilter);
    f_factory_.AddProducer("neg", ProduceNegativeFilter);
    f_factory_.AddProducer("sharp", ProduceSharpeningFilter);
}

// ./image_processor input.txt output.txt -crop 100 100 -gs -neg -sharp -blur 0.5

void Application::Start(int argc, char** argv) {
    try {
        cl_parser_.Parse(argc, argv, app_settings_);
        
        BMP bmp;
        bmp.ReadFromFile("./INPUT.bmp");
        Filter* filter = f_factory_.GetProducer("sharp")(app_settings_.filters_settings_[3]);
        filter->Apply(bmp);
        bmp.WriteToFile("./OUTPUT.bmp");
        
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }
}
#include "application.h"
#include <stdexcept>
#include "filter.h"
#include "pipeline.h"
#include "sharpening_filter.h"

void Application::Config() {
    f_factory_.AddProducer("crop", ProduceCropFilter);
    f_factory_.AddProducer("gs", ProduceGrayscaleFilter);
    f_factory_.AddProducer("neg", ProduceNegativeFilter);
    f_factory_.AddProducer("sharp", ProduceSharpeningFilter);
    f_factory_.AddProducer("edge", ProduceEdgeDetectionFilter);
}

// ./image_processor INPUT.bmp OUTPUT.bmp -crop 1000 1000 -gs

void Application::Start(int argc, char** argv) {
    try {
        cl_parser_.Parse(argc, argv, app_settings_);
        
        BMP bmp;
        bmp.ReadFromFile(app_settings_.input_file_path_);

        for (const FilterSettings& filter_settings : app_settings_.filters_settings_) {
            FilterProducer filter_producer = f_factory_.GetProducer(filter_settings.name_);
            if (!filter_producer) {
                throw std::runtime_error("Filter with the given name does not exist");
            }
            pipeline_.AddFilter(filter_producer(filter_settings));
        }

        pipeline_.ApplyPipeline(bmp);
        bmp.WriteToFile(app_settings_.output_file_path_);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }
}
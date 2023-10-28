#include "application.h"

void Application::Config() {
    f_factory_.AddProducer("crop", ProduceCropFilter);
    f_factory_.AddProducer("gs", ProduceGrayscaleFilter);
    f_factory_.AddProducer("neg", ProduceNegativeFilter);
    f_factory_.AddProducer("sharp", ProduceSharpeningFilter);
    f_factory_.AddProducer("edge", ProduceEdgeDetectionFilter);
    f_factory_.AddProducer("blur", ProduceGaussianBlurFilter);
}

void Application::Start(int argc, char** argv) {
    try {
        cl_parser_.Parse(argc, argv, app_settings_);

        for (const FilterSettings& filter_settings : app_settings_.filters_settings_) {
            FilterProducer filter_producer = f_factory_.GetProducer(filter_settings.name_);
            if (!filter_producer) {
                throw std::runtime_error("Filter with the given name does not exist");
            }
            pipeline_.AddFilter(filter_producer(filter_settings));
        }

        BMP bmp;

        auto start = std::chrono::system_clock::now().time_since_epoch().count();

        bmp.ReadFromFile(app_settings_.input_file_path_);
        Image image = bmp_image_converter_.GetImageFromBMP(bmp);
        pipeline_.ApplyPipeline(image);

        bmp = bmp_image_converter_.GetBMPFromImage(image, bmp.GetBMPHeader(), bmp.GetDIBHeader());
        bmp.WriteToFile(app_settings_.output_file_path_);

        auto now = std::chrono::system_clock::now().time_since_epoch().count();
        std::cerr << "Time elapsed: " << static_cast<double>(now - start) / CLOCKS_PER_SEC << "\n";

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }
}
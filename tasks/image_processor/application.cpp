#include "application.h"

void Application::Config() {
    f_factory_.AddProducer("crop", ProduceCropFilter);
    f_factory_.AddProducer("gs", ProduceGrayscaleFilter);
    f_factory_.AddProducer("neg", ProduceNegativeFilter);
    f_factory_.AddProducer("sharp", ProduceSharpeningFilter);
    f_factory_.AddProducer("edge", ProduceEdgeDetectionFilter);
    f_factory_.AddProducer("blur", ProduceGaussianBlurFilter);
    f_factory_.AddProducer("fisheye", ProduceFisheyeFilter);
}

void Application::Start(int argc, char** argv) {
    auto start_time = std::chrono::high_resolution_clock::now();

    try {
        // Getings application settings parsed from command line
        cl_parser_.Parse(argc, argv, app_settings_);

        // Assembling the pipeline by creating filters using the appropriate producers
        for (const FilterSettings& filter_settings : app_settings_.filters_settings_) {
            FilterProducer filter_producer = f_factory_.GetProducer(filter_settings.name_);
            if (!filter_producer) {
                throw std::invalid_argument("Filter with the given name does not exist.");
            }
            pipeline_.AddFilter(filter_producer(filter_settings));
        }

        // Reading .bmp file in the BMP class, converting it to the Image class and applying the pipeline
        // Then, creating the BMP from the modifyied Image.
        // Fields (except height and width) in BMP and DIB headers are copied from the previous version
        BMP bmp;
        bmp.ReadFromFile(app_settings_.input_file_path_);
        Image image = bmp_image_converter_.GetImageFromBMP(bmp);

        pipeline_.ApplyPipeline(image);

        bmp = bmp_image_converter_.GetBMPFromImage(image, bmp.GetBMPHeader(), bmp.GetDIBHeader());
        bmp.WriteToFile(app_settings_.output_file_path_);

    } catch (std::invalid_argument& e) {
        std::cerr << "Invalid input: " << e.what() << "\n";
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    } catch (...) {
        std::cerr << "Unknown exception.\n";
    }

    auto cur_time = std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds dur = std::chrono::duration_cast<std::chrono::milliseconds>(cur_time - start_time);

    std::cerr << "Time elapsed: " << dur.count() << "ms.\n";
}
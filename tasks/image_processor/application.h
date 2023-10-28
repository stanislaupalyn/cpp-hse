#pragma once

#include <chrono>
#include <stdexcept>

#include "application_settings.h"
#include "bmp.h"
#include "bmp_image_converter.h"
#include "command_line_parser.h"
#include "filter.h"
#include "filter_factory.h"
#include "image.h"
#include "pipeline.h"
#include "rgb_color.h"

/// Filters
#include "crop_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"

class Application {
private:
    ApplicationSettings app_settings_;
    CommandLineParser cl_parser_;
    FilterFactory f_factory_;
    Pipeline pipeline_;
    BMPImageConverter bmp_image_converter_;

public:
    void Config();
    void Start(int argc, char* argv[]);
};
#pragma once

#include "command_line_parser.h"
#include "filter_factory.h"
#include "application_settings.h"
#include "pipeline.h"
#include "bmp.h"

#include "filter.h"
#include "crop_filter.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "edge_detection_filter.h"
#include "bmp_image_converter.h"

#include <stdexcept>
#include "sharpening_filter.h"

#include "rgb_color.h"
#include "image.h"

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
#pragma once

#include "command_line_parser.h"
#include "filter_factory.h"
#include "filter.h"
#include "crop_filter.h"
#include "application_settings.h"
#include "bmp.h"

class Application {
private:
    ApplicationSettings app_settings_;
    CommandLineParser cl_parser_;
    FilterFactory f_factory_;
public:
    void Config();
    void Start(int argc, char* argv[]);

};
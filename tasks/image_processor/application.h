#pragma once

#include "command_line_parser.h"
#include "filter_factory.h"
#include "filter.h"
#include "application_settings.h"


class Application {
private:
    ApplicationSettings app_settings_;
    // CommandLineParser cl_parser_;
    // FilterFactory f_factory_;
public:
    void Config();
    void Start(int argc, char* argv[]);
        // cl_parser_.Parse(argc, argv, app_settings_);
    //     try {

    //     } catch(bad filter arguments)
};
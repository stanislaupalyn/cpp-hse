#include "command_line_parser.h"

void CommandLineParser::Parse(int argc, char* argv[], ApplicationSettings& app_settings) {
    if (argc < 3) {
        throw std::runtime_error("Input or output file is not specified.");
    }
    app_settings.input_file_path_ = argv[1];
    app_settings.output_file_path_ = argv[2];

    for (size_t i = 3; i < argc; ++i) {
        if (argv[i][0] == '-') {
            FilterSettings filter_settings;
            filter_settings.name_ = std::string(argv[i]).substr(1);

            size_t ptr = i + 1;
            while (ptr < argc && argv[ptr][0] != '-') {
                filter_settings.arguments_.push_back(argv[ptr]);
                ++ptr;
            }

            i = ptr - 1;
            app_settings.filters_settings_.push_back(filter_settings);
        }
    }
}
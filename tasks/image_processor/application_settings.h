#pragma once

#include "filter.h"
#include <string>

class ApplicationSettings {
    std::string input_file_path_;
    std::string output_file_path_;
    std::vector<FilterSettings> filters_settings_;
};
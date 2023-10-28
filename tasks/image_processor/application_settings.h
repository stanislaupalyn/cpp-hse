#pragma once

#include <string>

#include "filter.h"

struct ApplicationSettings {
    std::string input_file_path_;
    std::string output_file_path_;
    std::vector<FilterSettings> filters_settings_;
};
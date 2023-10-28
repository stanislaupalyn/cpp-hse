#pragma once

#include <iostream>
#include <stdexcept>

#include "application_settings.h"

class CommandLineParser {

public:
    void Parse(int argc, char* argv[], ApplicationSettings& app_settings);
};
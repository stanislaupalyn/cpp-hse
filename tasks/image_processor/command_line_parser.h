#pragma once

#include "application_settings.h"
#include <iostream>

class CommandLineParser {

public:
    void Hello();
    void Parse(int argc, char* argv[], ApplicationSettings& app_settings);
};
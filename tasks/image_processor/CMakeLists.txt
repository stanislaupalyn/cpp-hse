add_library(application STATIC application.cpp)
add_library(application_settings STATIC application_settings.cpp)
add_library(command_line_parser STATIC command_line_parser.cpp)
add_library(filter_factory STATIC filter_factory.cpp)
add_library(filter STATIC filter.cpp)

add_executable(image_processor image_processor.cpp)

target_link_libraries(image_processor application)

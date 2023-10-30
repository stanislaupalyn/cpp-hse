# add_library(application STATIC application.cpp)
# add_library(application_settings STATIC application_settings.cpp)
# add_library(command_line_parser STATIC command_line_parser.cpp)
# add_library(filter_factory STATIC filter_factory.cpp)
# add_library(filter STATIC filter.cpp)
# add_library(bmp STATIC bmp.cpp)

add_executable(image_processor image_processor.cpp 
               application application.cpp
               application_settings application_settings.cpp
               command_line_parser command_line_parser.cpp
               filter_factory filter_factory.cpp
               bmp bmp.cpp
               filter filter.cpp
               crop_filter crop_filter.cpp
               grayscale_filter grayscale_filter.cpp
               negative_filter negative_filter.cpp
               sharpening_filter sharpening_filter.cpp
               edge_detection_filter edge_detection_filter.cpp
               pipeline pipeline.cpp
               rgb_color rgb_color.cpp
               image image.cpp
               bmp_image_converter bmp_image_converter.cpp
               gaussian_blur_filter gaussian_blur_filter.cpp
               fisheye_filter fisheye_filter.cpp)


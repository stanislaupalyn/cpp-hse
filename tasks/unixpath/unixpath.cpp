#include "unixpath.h"

#include <algorithm>
#include <cstdint>
#include <string>

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string normalized_path{path.begin(), path.end()};
    for (size_t index = 0; index < normalized_path.size(); ++index) {
        if (normalized_path[index] == '.' &&
            (index == normalized_path.size() - 1 || normalized_path[index + 1] != '.') &&
            (index == 0 || normalized_path[index - 1] != '.')) {
            normalized_path.erase(index, 1);
            --index;
        }
    }

    int32_t moves_up = 0;
    for (size_t index = 0; index + 1 < normalized_path.size(); ++index) {
        if (normalized_path[index] == '.' && normalized_path[index + 1] == '.') {
            ++moves_up;
            normalized_path.erase(index, 2);
            --index;
        }
    }

    for (size_t index = 0; index + 1 < normalized_path.size(); ++index) {
        if (normalized_path[index] == '/' && normalized_path[index + 1] == '/') {
            normalized_path.erase(index, 1);
            --index;
        }
    }

    if (normalized_path.size() == 0) {
        normalized_path = "/";
    }

    for (size_t index = current_working_dir.size() - 1; ~index; --index) {
        if (current_working_dir[index] == '/') {
            --moves_up;
        }
        if (moves_up == 0) {
            assert(normalized_path[0] == '/');
            normalized_path = static_cast<std::string>(current_working_dir.substr(0, index)) + normalized_path;
            break;
        }
    }

    if (normalized_path.back() == '/') {
        normalized_path.pop_back();
    }
    if (normalized_path.front() != '/') {
        normalized_path = "/" + normalized_path;
    }

    return normalized_path;
}

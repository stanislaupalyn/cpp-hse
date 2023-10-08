#include "unixpath.h"

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string>

void DeleteDoubleSlashes(std::string& path) {
    std::string new_path;
    for (size_t i = 0; i < path.size(); ++i) {
        if (i > 0 && path[i] == '/' && path[i - 1] == '/') {
            continue;
        }
        new_path += path[i];
    }
    path = new_path;
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::string full_path{path};
    if (path[0] != '/') {
        full_path = static_cast<std::string>(current_working_dir) + "/" + full_path;
    }
    full_path += "/";
    DeleteDoubleSlashes(full_path);

    std::string current_path;
    for (size_t i = 0; i < full_path.size(); ++i) {
        if (full_path[i] == '/') {
            size_t next_slash = full_path.find('/', i + 1);
            std::string token = full_path.substr(i + 1, next_slash - i - 1);
            if (token == "..") {
                while (current_path.size() > 1 && current_path.back() != '/') {
                    current_path.pop_back();
                }
            } else {
                if (token != ".") {
                    current_path += "/";
                    current_path += token;
                }
            }
            i = next_slash - 1;
        }
    }

    DeleteDoubleSlashes(current_path);
    if (current_path.size() > 1 && current_path.back() == '/') {
        current_path.pop_back();
    }

    return current_path;
}
#include "search.h"

#include <cmath>
#include <map>
#include <numeric>
#include <sstream>
#include <string_view>

std::vector<std::string_view> GetWords(const std::string_view line) {
    std::vector<std::string_view> words;
    for (size_t i = 0; i < line.size(); ++i) {
        if (isalpha(line[i])) {
            size_t right_index = i;
            while (right_index < line.size() && std::isalpha(line[right_index])) {
                ++right_index;
            }
            words.emplace_back(line.substr(i, right_index - i));
            i = right_index - 1;
        }
    }
    return words;
}

std::string GetNormalizedWord(const std::string_view word) {
    std::string result{word};
    for (size_t i = 0; i < word.size(); ++i) {
        result[i] = static_cast<char>(std::tolower(result[i]));
    }
    return result;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::vector<std::string_view> query_words = GetWords(query);

    std::sort(query_words.begin(), query_words.end());
    query_words.erase(unique(query_words.begin(), query_words.end()), query_words.end());

    size_t number_lines = 0;
    std::map<std::string, size_t> number_of_word;
    std::map<std::string, size_t> number_of_lines_with_word;

    std::vector<std::vector<std::string_view>> lines_words;
    std::vector<std::string_view> lines;

    for (size_t i = 0; i < text.size(); ++i) {
        size_t right_index = i;
        while (right_index < text.size() && text[right_index] != '\n') {
            ++right_index;
        }

        std::string_view line = text.substr(i, right_index - i);
        i = right_index;

        std::vector<std::string_view> line_words = GetWords(line);
        if (line_words.empty()) {
            continue;
        }
        lines_words.emplace_back(line_words);
        lines.emplace_back(line);

        ++number_lines;
        number_of_word.clear();
        for (const std::string_view word : line_words) {
            ++number_of_word[GetNormalizedWord(word)];
        }
        for (const std::pair<std::string, size_t> word_and_number : number_of_word) {
            ++number_of_lines_with_word[word_and_number.first];
        }
    }

    std::vector<double> line_value(lines.size());

    for (size_t i = 0; i < lines_words.size(); ++i) {
        const std::vector<std::string_view>& line_words = lines_words[i];

        number_of_word.clear();
        for (const std::string_view word : line_words) {
            ++number_of_word[GetNormalizedWord(word)];
        }

        for (const std::string_view query_word : query_words) {
            std::string word = GetNormalizedWord(query_word);

            double tf_value = static_cast<double>(number_of_word[word]) / static_cast<double>(line_words.size());
            double idf_value = static_cast<double>(number_of_lines_with_word[word]) / static_cast<double>(number_lines);
            line_value[i] += tf_value * std::log(1 / idf_value);
        }
    }

    std::vector<size_t> order_lines(lines.size());
    std::iota(order_lines.begin(), order_lines.end(), 0);

    std::stable_sort(order_lines.begin(), order_lines.end(),
                     [&line_value](size_t i, size_t j) { return line_value[i] > line_value[j]; });

    std::vector<std::string_view> result;
    for (size_t i = 0; i < std::min(results_count, lines.size()); ++i) {
        if (line_value[order_lines[i]] == 0) {
            break;
        }
        result.emplace_back(lines[order_lines[i]]);
    }

    return result;
}

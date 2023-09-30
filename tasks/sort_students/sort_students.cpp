#include "sort_students.h"

#include <algorithm>

// Date comparison
bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.year != rhs.year) {
        return lhs.year < rhs.year;
    }
    if (lhs.month != rhs.month) {
        return lhs.month < rhs.month;
    }
    return lhs.day < rhs.day;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    switch (sortKind) {
        case SortKind::Name:
            sort(students.begin(), students.end(), [](const Student& lhs, const Student& rhs) {
                return std::tie(lhs.last_name, lhs.name, lhs.birth_date) <
                       std::tie(rhs.last_name, rhs.name, rhs.birth_date);
            });
            break;

        case SortKind::Date:
            sort(students.begin(), students.end(), [](const Student& lhs, const Student& rhs) {
                return std::tie(lhs.birth_date, lhs.last_name, lhs.name) <
                       std::tie(rhs.birth_date, rhs.last_name, rhs.name);
            });
            break;
    }
}

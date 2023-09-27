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
    return lhs.year == rhs.year && lhs.month == rhs.month && lhs.day == rhs.day;
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

void SortStudents(std::vector<Student>& students, SortKind sortKind) {
    if (sortKind == SortKind::Name) {
        sort(students.begin(), students.end(), [](const Student& lhs, const Student& rhs) {
            if (lhs.last_name != rhs.last_name) {
                return lhs.last_name < rhs.last_name;
            }
            if (lhs.name != rhs.name) {
                return lhs.name < rhs.name;
            }
            return lhs.birth_date < rhs.birth_date;
        });
    }
    if (sortKind == SortKind::Date) {
        sort(students.begin(), students.end(), [](const Student& lhs, const Student& rhs) {
            if (lhs.birth_date != rhs.birth_date) {
                return lhs.birth_date < rhs.birth_date;
            }
            if (lhs.last_name != rhs.last_name) {
                return lhs.last_name < rhs.last_name;
            }
            return lhs.name < rhs.name;
        });
    }
}

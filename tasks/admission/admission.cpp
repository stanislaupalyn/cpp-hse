#include "admission.h"

#include <algorithm>

// Date comparison
bool operator<(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator==(const Date& lhs, const Date& rhs) {
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

AdmissionTable FillUniversities(const std::vector<University>& universities, const std::vector<Applicant>& applicants) {
    std::vector<std::pair<Applicant, const Student*>> applicants_order;
    for (const auto& applicant : applicants) {
        applicants_order.push_back({applicant, &applicant.student});
    }

    std::sort(applicants_order.begin(), applicants_order.end(),
              [](const std::pair<Applicant, const Student*>& lhs, const std::pair<Applicant, const Student*>& rhs) {
                  if (lhs.first.points != rhs.first.points) {
                      return lhs.first.points > rhs.first.points;
                  }
                  return std::tie(lhs.first.student.birth_date, lhs.first.student.name) <
                         std::tie(rhs.first.student.birth_date, rhs.first.student.name);
              });

    AdmissionTable result;

    std::unordered_map<std::string, size_t> max_students_of;
    for (const auto& university : universities) {
        max_students_of[university.name] = university.max_students;
    }

    for (const auto& current : applicants_order) {
        for (const auto& university_name : current.first.wish_list) {
            if (result[university_name].size() < max_students_of[university_name]) {
                result[university_name].push_back(current.second);
                break;
            }
        }
    }

    for (auto& students_list : result) {
        sort(students_list.second.begin(), students_list.second.end(), [](const Student* a, const Student* b) {
            return std::tie(a->name, a->birth_date) < std::tie(b->name, b->birth_date);
        });
    }

    return result;
}

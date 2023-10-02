#include "tests_checking.h"

#include <deque>

std::vector<std::string> StudentsOrder(const std::vector<StudentAction>& student_actions,
                                       const std::vector<size_t>& queries) {
    std::deque<std::string> order;
    for (const auto& current : student_actions) {
        if (current.side == Side::Top) {
            order.push_front(current.name);
        } else {
            order.push_back(current.name);
        }
    }

    std::vector<std::string> answer;
    for (const auto& index : queries) {
        answer.push_back(order[index - 1]);
    }
    return answer;
}

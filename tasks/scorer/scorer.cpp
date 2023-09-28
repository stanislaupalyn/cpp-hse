#include "scorer.h"

struct ProblemStatus {
    bool is_last_success = false;
    bool is_merge_request_closed = true;
};

ScoreTable GetScoredStudents(const Events& events, time_t score_time) {
    Events events_order;
    for (const auto& current : events) {
        events_order.push_back(current);
    }

    std::sort(events_order.begin(), events_order.end(),
              [](const Event& lhs, const Event& rhs) { return lhs.time < rhs.time; });

    std::map<std::pair<StudentName, TaskName>, ProblemStatus> status_of;
    for (const auto& current_event : events) {
        if (current_event.time > score_time) {
            break;
        }

        switch (current_event.event_type) {
            case EventType::CheckSuccess:
                status_of[{current_event.student_name, current_event.task_name}].is_last_success = true;
                ;
                break;

            case EventType::CheckFailed:
                status_of[{current_event.student_name, current_event.task_name}].is_last_success = false;
                break;

            case EventType::MergeRequestClosed:
                status_of[{current_event.student_name, current_event.task_name}].is_merge_request_closed = true;
                break;

            case EventType::MergeRequestOpen:
                status_of[{current_event.student_name, current_event.task_name}].is_merge_request_closed = false;
                break;
        }
    }

    ScoreTable result;
    for (const auto& problem : status_of) {
        if (problem.second.is_last_success && problem.second.is_merge_request_closed) {
            result[problem.first.first].insert(problem.first.second);
        }
    }

    return result;
}

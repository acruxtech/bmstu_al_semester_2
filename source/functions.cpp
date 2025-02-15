#include <string>
#include <vector>
#include <algorithm>

#include "../include/header.h"


float AvgValue(const std::vector<unsigned>& seq) {
    unsigned sum = 0;
    for (unsigned value : seq) {
        sum += value;
    }
    return static_cast<float>(sum) / seq.size();
}


void SortByName(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}


void SortByRating(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return AvgValue(a.Ratings) < AvgValue(b.Ratings);
    });
}


size_t CountTwoness(const std::vector<Student>& students) {
    size_t res = 0;
    for (Student student : students) {
        for (int rating : student.Ratings) {
            if (rating <= 2) {
                res += 1;
                break;
            }
        }
    }
    return res;
}


size_t CountExcellent(const std::vector<Student>& students) {
    size_t res = 0;
    for (Student student : students) {
        bool flag = true; 
        for (int rating : student.Ratings) {
            if (rating != 5) flag = false;
        }
        res += static_cast<size_t>(flag);
    }
    return res;
}


std::vector<Student> VectorMathExcellent(const std::vector<Student>& students) {
    std::vector<Student> new_students;
    for (Student student : students) {
        auto math_id = std::find(student.Subjects.begin(), student.Subjects.end(), "Math");
        if (math_id == student.Subjects.end()) {
            continue;
        }
        if (student.Ratings[math_id - student.Subjects.begin()] == 5) {
            new_students.push_back(student);
        }
    } 
    return new_students;
}


std::vector<std::string> GroupsId(const std::vector<Student>& students) {
    std::vector<std::string> group_ids;
    for (Student student : students) {
        auto finded_group_id = std::find(group_ids.begin(), group_ids.end(), student.GroupId);
        if (finded_group_id == group_ids.end()) group_ids.push_back(student.GroupId);
    }
    return group_ids;
}


std::vector<Group> Groups(const std::vector<Student>& students) {
    std::vector<Group> groups;
    for (std::string group_id : GroupsId(students)) {
        groups.push_back({
            group_id,
            {},
        });
    }
    for (Student student : students) {
        auto finded_group = std::find_if(
            groups.begin(), 
            groups.end(), 
            [&student](const Group& group) { return group.Id == student.GroupId; }
        );
        groups[finded_group - groups.begin()].Students.push_back(student);
    }
    return groups;
}

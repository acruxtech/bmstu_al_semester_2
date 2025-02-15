#include <vector>
#include <algorithm>

#include "../include/Group.h"


float Group::AvgValue(const std::vector<unsigned>& seq) {
    unsigned sum = 0;
    for (unsigned value : seq) {
        sum += value;
    }
    return static_cast<float>(sum) / seq.size();
}


void Group::AddStudent(const Student& student) {
    Students.push_back(student);
}


void Group::RemoveStudent(const int& studentId) {
    for (auto it = Students.begin(); it != Students.end(); ++it) {
        if (it->Id == studentId) {
            Students.erase(it);
            break;
        }
    }
}


std::vector<Student> Group::FindStudents(const std::string& subseq) {
    std::vector<Student> foundStudents;
    for (const auto& student : Students) {
        if (student.Name.find(subseq) != std::string::npos) {
            foundStudents.push_back(student);
        }
    }
    return foundStudents;
}


Student* Group::FindStudent(const std::string& name) {
    for (auto& student : Students) {
        if (student.Name == name) {
            return &student;
        }
    }
    return nullptr;
}


void Group::SortByName() {
    std::sort(Students.begin(),Students.end(), [](const Student& a, const Student& b) {
        return a.Name < b.Name;
    });
}


void Group::SortByRating() {
    std::sort(Students.begin(), Students.end(), [](const Student& a, const Student& b) {
        return AvgValue(a.Ratings) < AvgValue(b.Ratings);
    });
}


size_t Group::CountTwoness() {
    size_t res = 0;
    for (Student student : Students) {
        for (int rating : student.Ratings) {
            if (rating <= 2) {
                res += 1;
                break;
            }
        }
    }
    return res;
}


size_t Group::CountExcellent() {
    size_t res = 0;
    for (Student student : Students) {
        bool flag = true; 
        for (int rating : student.Ratings) {
            if (rating != 5) flag = false;
        }
        res += static_cast<size_t>(flag);
    }
    return res;
}


std::vector<Student> Group::VectorMathExcellent() {
    std::vector<Student> new_students;
    for (Student student : Students) {
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

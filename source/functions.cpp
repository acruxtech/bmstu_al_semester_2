#include "../include/header.hpp"
#include <algorithm>
#include <numeric>
#include <set>
#include <map>


void SortByName(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(), 
        [](const Student& a, const Student& b) {
            return a.Name < b.Name;
        });
}


double CalculateAverageRating(const Student& student) {
    if (student.Ratings.empty()) return 0.0;
    return std::accumulate(student.Ratings.begin(), student.Ratings.end(), 0.0) / student.Ratings.size();
}


void SortByRating(std::vector<Student>& students) {
    std::sort(students.begin(), students.end(),
        [](const Student& a, const Student& b) {
            return CalculateAverageRating(a) > CalculateAverageRating(b);
        });
}


size_t CountTwoness(const std::vector<Student>& students) {
    size_t count = 0;
    for (const auto& student : students) {
        bool hasTwoness = false;
        for (unsigned rating : student.Ratings) {
            if (rating < 3) {
                hasTwoness = true;
                break;
            }
        }
        if (hasTwoness) {
            count++;
        }
    }
    return count;
}


size_t CountExcellent(const std::vector<Student>& students) {
    size_t excellentCount = 0;
    
    for (const auto& student : students) {
        bool allExcellent = true;
        
        for (unsigned rating : student.Ratings) {
            if (rating != 5) {
                allExcellent = false;
                break;
            }
        }
        
        if (allExcellent && !student.Ratings.empty()) {
            excellentCount++;
        }
    }
    
    return excellentCount;
}


std::vector<Student> VectorMathExcellent(const std::vector<Student>& students) {
    std::vector<Student> result;
    for (const auto& student : students) {
        for (size_t i = 0; i < student.Subjects.size(); ++i) {
            if (student.Subjects[i] == "Math" && student.Ratings[i] == 5) {
                result.push_back(student);
                break;
            }
        }
    }
    return result;
}


std::vector<std::string> GroupsId(const std::vector<Student>& students) {
    std::set<std::string> uniqueGroups;
    for (const auto& student : students) {
        uniqueGroups.insert(student.GroupId);
    }
    return std::vector<std::string>(uniqueGroups.begin(), uniqueGroups.end());
}


std::vector<Group> Groups(const std::vector<Student>& students) {
    std::map<std::string, std::vector<Student>> groupsMap;
    for (const auto& student : students) {
        groupsMap[student.GroupId].push_back(student);
    }
    
    std::vector<Group> result;
    for (const auto& [groupId, studentsInGroup] : groupsMap) {
        result.push_back({groupId, studentsInGroup});
    }
    
    return result;
}
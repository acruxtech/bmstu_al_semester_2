#include <iostream>
#include <vector>

#include "../include/header.h"


int main() {
    std::vector<Student> students = {
        {
            "Иван Иванов",
            "1",
            {4, 5, 5},
            {"Math", "Физика", "Информатика"}
        },
        {
            "Петр Петров",
            "2",
            {4, 5, 4},
            {"Физика", "Math", "Химия"}
        },
        {
            "Сергей Сергеев",
            "1",
            {4, 5, 2},
            {"Math", "Физика", "Биология"}
        },
        {
            "Алексей Алексеев",
            "3",
            {5, 5, 5},
            {"Math", "Физика", "Информатика"}
        },
        {
            "Дмитрий Дмитриев",
            "2",
            {4, 4, 4},
            {"Математика", "Физика", "Химия"}
        }
    };

    std::cout << "Исходный список студентов:" << std::endl;
    for (Student el : students) {
        std::cout << el.Name << std::endl;
    }
    std::cout << "----" << std::endl;

    std::cout << "Список, отсортированный в алфавитном порядке:" << std::endl;
    SortByName(students);
    for (Student el : students) {
        std::cout << el.Name << std::endl;
    }
    std::cout << "----" << std::endl;

    std::cout << "Список, отсортированный по средней оценке (по возрастанию):" << std::endl;
    SortByRating(students);
    for (Student el : students) {
        std::cout << el.Name << " (ср. балл " << AvgValue(el.Ratings) << ")" << std::endl;
    }
    std::cout << "----" << std::endl;

    std::cout << "Количество двоечников: " << CountTwoness(students) << std::endl;
    std::cout << "----" << std::endl;

    std::cout << "Количество отличников: " << CountExcellent(students) << std::endl;
    std::cout << "----" << std::endl;

    std::cout << "Список отличников по математике:" << std::endl;
    for (auto el : VectorMathExcellent(students)) {
        std::cout << el.Name << std::endl;
    }
    std::cout << "----" << std::endl;
    std::cout << "Список id групп:" << std::endl;
    for (auto el : GroupsId(students)) {
        std::cout << el << " ";
    }
    std::cout << "\n----" << std::endl;

    std::cout << "Список студентов по группам:" << std::endl;
    for (Group group : Groups(students)) {
        std::cout << "\nСтуденты группы " << group.Id << std::endl;
        for (Student student : group.Students) {
            std::cout << " - " << student.Name << std::endl;
        }
    }
}
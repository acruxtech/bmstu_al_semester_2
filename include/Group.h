#include <string>
#include <vector>
#include "../include/Student.h"


class Group
{
    private:
        std::string Id;
        std::vector<Student> Students;

    public:
        Group(const std::string& id) {
            this->Id = id;
        }

        void AddStudent(const Student& student);

        void RemoveStudent(const int& studentId);

        // Возвращает список студентов, в имени которых встречается данная подстрока
        std::vector<Student> FindStudents(const std::string& subseq);

        // Возвращает студента с данным именем
        Student* FindStudent(const std::string& name);

        void SortByName();

        void SortByRating();

        size_t CountTwoness();

        size_t CountExcellent();

        std::vector<Student> VectorMathExcellent();

    private:
        static float AvgValue(const std::vector<unsigned>& seq);
};

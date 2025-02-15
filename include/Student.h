#include <string>
#include <vector>


struct Student
{
    int Id;
    std::string Name;
    std::string GroupId;
    std::vector<unsigned> Ratings;
    std::vector<std::string> Subjects;
};

#include <iostream>
#include <fstream>
#include <vector>
#include <deque>
#include <algorithm>
#include <string>


class Car {
    private:
        std::string model;
        double fuel_consumption[3];     // [0] - трасса, [1] - город, [2] - смешанный
        int max_speed;
        int power;

    public:
        Car() : model(""), max_speed(0), power(0) {
            fuel_consumption[0] = fuel_consumption[1] = fuel_consumption[2] = 0.0;
        }

        Car(const std::string& m, double highway, double city, double mixed, int speed, int pwr) 
            : model(m), max_speed(speed), power(pwr) {
            fuel_consumption[0] = highway;
            fuel_consumption[1] = city;
            fuel_consumption[2] = mixed;
        }

        Car(const Car& other) = default;
        Car& operator=(const Car& other) = default;

        friend std::ostream& operator<<(std::ostream& os, const Car& car) {
            os << "Модель: " << car.model 
            << "\nРасход топлива (трасса/город/смешанный): " 
            << car.fuel_consumption[0] << "/" 
            << car.fuel_consumption[1] << "/" 
            << car.fuel_consumption[2]
            << "\nМаксимальная скорость: " << car.max_speed << " км/ч"
            << "\nМощность: " << car.power << " л.с.\n";
            return os;
        }

        bool operator<(const Car& other) const {
            return model < other.model;
        }

        const std::string& getModel() const { return model; }

        const double* getFuelConsumption() const { return fuel_consumption; }

        int getMaxSpeed() const { return max_speed; }

        int getPower() const { return power; }
};


void readCarsFromFile(std::vector<Car>& cars, const std::string& filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        std::cerr << "Ошибка открытия входного файла!" << std::endl;
        return;
    }

    std::string model;
    double highway, city, mixed;
    int speed, power;

    while (in >> model >> highway >> city >> mixed >> speed >> power) {
        cars.emplace_back(model, highway, city, mixed, speed, power);
    }
    in.close();
}


template<typename Container>
void writeToFile(const std::string& title, const Container& container, std::ofstream& out) {
    out << "\n=== " << title << " ===\n";
    for (const auto& car : container) {
        out << car << "\n";
    }
}


int main() {
    std::vector<Car> cars;
    readCarsFromFile(cars, "input.txt");

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        return 1;
    }

    writeToFile("Исходный вектор", cars, out);

    std::sort(cars.begin(), cars.end());
    writeToFile("Отсортированный вектор", cars, out);

    std::deque<Car> cars_deque;
    std::copy(cars.begin(), cars.end(), std::back_inserter(cars_deque));
    writeToFile("Скопированный двусторонняя очередь", cars_deque, out);

    out.close();
    return 0;
}

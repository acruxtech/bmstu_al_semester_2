#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_set>
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

        bool operator<(const Car& other) const {
            return model < other.model;
        }

        bool operator==(const Car& other) const {
            return model == other.model &&
                max_speed == other.max_speed &&
                power == other.power &&
                fuel_consumption[0] == other.fuel_consumption[0] &&
                fuel_consumption[1] == other.fuel_consumption[1] &&
                fuel_consumption[2] == other.fuel_consumption[2];
        }

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

        friend struct CarHash;
};


struct CarHash {
    size_t operator()(const Car& car) const {
        size_t h1 = std::hash<std::string>()(car.model);
        size_t h2 = std::hash<double>()(car.fuel_consumption[0]);
        size_t h3 = std::hash<double>()(car.fuel_consumption[1]);
        size_t h4 = std::hash<double>()(car.fuel_consumption[2]);
        size_t h5 = std::hash<int>()(car.max_speed);
        size_t h6 = std::hash<int>()(car.power);
        return h1 ^ (h2 << 1) ^ (h3 << 2) ^ (h4 << 3) ^ (h5 << 4) ^ (h6 << 5);
    }
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

    std::set<Car> car_set;
    std::unordered_set<Car, CarHash> car_unordered_set;

    for (const auto& car : cars) {
        car_set.insert(car);
        car_unordered_set.insert(car);
    }

    std::ofstream out("output.txt");
    if (!out.is_open()) {
        std::cerr << "Ошибка открытия выходного файла!" << std::endl;
        return 1;
    }

    writeToFile("Исходные данные (vector)", cars, out);
    writeToFile("Упорядоченный набор (set)", car_set, out);
    writeToFile("Неупорядоченный набор (unordered_set)", car_unordered_set, out);

    return 0;
}

#include <iostream>
using namespace std;


class Square {
    protected:
        double side_length;

    public:
        Square(double length) : side_length(length) {}

        virtual double calculateArea() const {
            return side_length * side_length;
        }

        virtual void printInfo() const {
            cout << "Квадрат:" << endl;
            cout << "  Длина стороны: " << side_length << endl;
            cout << "  Площадь: " << calculateArea() << endl;
        }
};


class Cube : public Square {
    public:
        Cube(double length) : Square(length) {}

        // статический полиморфизм
        double calculateVolume() const {
            return Square::calculateArea() * side_length;
        }

        // динамический полиморфизм
        double calculateArea() const override {
            return 6 * Square::calculateArea();
        }

        void printInfo() const override {
            cout << "Куб:" << endl;
            cout << "  Длина ребра: " << side_length << endl;
            cout << "  Площадь поверхности: " << calculateArea() << endl;
            cout << "  Объем: " << calculateVolume() << endl;
        }
};

int main() {
    cout << "=== Статический полиморфизм ===" << endl;
    Square square(5);
    square.printInfo();

    Cube cube(3);
    cube.printInfo();

    cout << "\n=== Динамический полиморфизм ===" << endl;
    Square* shape1 = new Square(4); 
    Square* shape2 = new Cube(2); 

    shape1->printInfo();
    delete shape1;

    shape2->printInfo();
    delete shape2;

    return 0;
}

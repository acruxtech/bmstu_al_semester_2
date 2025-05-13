#include <iostream>
#include <cmath>
#include <stdexcept>
#include <string>


class QuadraticEquationException : public std::invalid_argument {
    private:
        double a, b, c;
        double discriminant;
        
    public:
        QuadraticEquationException(const std::string& msg, double a, double b, double c, double d)
            : invalid_argument(msg), a(a), b(b), c(c), discriminant(d) {}
        
        void printDetails() const {
            std::cerr << "Ошибка в квадратном уравнении: " << what() << std::endl;
            std::cerr << "Коэффициенты: a = " << a << ", b = " << b << ", c = " << c << std::endl;
            std::cerr << "Дискриминант: " << discriminant << " (отрицательный)" << std::endl;
        }
};


class QuadraticEquation {
    private:
        double a, b, c;
        
    public:
        QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {
            if (a == 0) {
                throw std::invalid_argument("Коэффициент 'a' не может быть нулевым");
            }
        }
        
        double calculateDiscriminant() const {
            return b * b - 4 * a * c;
        }
        
        void solve() const {
            double d = calculateDiscriminant();
            
            if (d < 0) {
                throw QuadraticEquationException("Уравнение не имеет действительных корней", a, b, c, d);
            }
            
            double sqrt_d = sqrt(d);
            double x1 = (-b + sqrt_d) / (2 * a);
            double x2 = (-b - sqrt_d) / (2 * a);
            
            std::cout << "Корни уравнения: x1 = " << x1 << ", x2 = " << x2 << std::endl;
        }
        
        void printEquation() const {
            std::cout << "Уравнение: " << a << "x² + " << b << "x + " << c << " = 0" << std::endl;
        }
};


int main() {
    try {
        QuadraticEquation eq1(1, -5, 6);
        eq1.printEquation();
        eq1.solve();
        
        QuadraticEquation eq2(1, 2, 5);
        eq2.printEquation();
        eq2.solve();
    }
    catch (const QuadraticEquationException& e) {
        std::cerr << "\nИсключение:" << std::endl;
        e.printDetails();
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    
    return 0;
}

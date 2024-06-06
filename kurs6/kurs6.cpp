#include <iostream>
#include <string>
#include <map>
#include <sstream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

class Monomial {
private:
    map<char, int> powers; // Набор степеней переменных
    int coefficient; // Коэффициент

public:
    // Конструкторы
    Monomial() : coefficient(0) {}
    Monomial(int coeff) : coefficient(coeff) {}
    Monomial(const char* monomial) {
        stringstream ss(monomial);
        char ch;
        int coeff, power;
        ss >> coeff;
        coefficient = coeff;
        while (ss >> ch) {
            if (ch == '^') {
                ss >> power;
                powers[ss.peek()] = power;
                ss.ignore(); // Пропускаем символ переменной
            }
            else {
                powers[ch] = 1;
            }
        }
    }

    // Методы доступа к членам класса
    int getCoefficient() const {
        return coefficient;
    }

    const map<char, int>& getPowers() const {
        return powers;
    }

    // Перегруженные операторы
    Monomial& operator+=(const Monomial& other) {
        if (powers == other.powers) {
            coefficient += other.coefficient;
        }
        else {
            cerr << "Monomials have different variables and/or powers." << endl;
        }
        return *this;
    }

    friend Monomial operator+(Monomial lhs, const Monomial& rhs) {
        lhs += rhs;
        return lhs;
    }

    Monomial& operator-=(const Monomial& other) {
        if (powers == other.powers) {
            coefficient -= other.coefficient;
        }
        else {
            cerr << "Monomials have different variables and/or powers." << endl;
        }
        return *this;
    }

    friend Monomial operator-(Monomial lhs, const Monomial& rhs) {
        lhs -= rhs;
        return lhs;
    }

    Monomial& operator*=(const Monomial& other) 
    {
        coefficient *= other.coefficient;
        for (const auto& [var, power] : other.powers)  
        {
            powers[var] += power; 
        }
        return *this;
    }

    friend Monomial operator*(Monomial lhs, const Monomial& rhs) {
        lhs *= rhs;
        return lhs;
    }

    bool operator==(const Monomial& other) const {
        return (coefficient == other.coefficient && powers == other.powers);
    }

    bool operator!=(const Monomial& other) const {
        return !(*this == other);
    }

    // Перегрузка операторов ввода/вывода
    friend ostream& operator<<(ostream& os, const Monomial& monomial) {
        os << monomial.coefficient;
        for (const auto& [var, power] : monomial.powers) { 
            os << var;
            if (power != 1) {
                os << "^" << power;
            }
        }
        return os;
    }

    friend istream& operator>>(istream& is, Monomial& monomial) {
        string input;
        is >> input;
        monomial = Monomial(input.c_str());
        return is;
    }
};



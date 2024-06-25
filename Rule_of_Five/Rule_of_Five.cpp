#include <iostream>
#include <cstring>

class MyString {
private:
    char* str;  // ��������� �� ������

public:
    // ����������� �� ���������
    MyString() : str(nullptr) {
        std::cout << "Default constructor called" << std::endl;
    }

    // ����������� � ���������� (����������� �����������)
    MyString(const char* s) : str(nullptr) {
        std::cout << "Constructor with parameter called" << std::endl;
        if (s != nullptr) {
            str = new char[std::strlen(s) + 1];
            std::strcpy(str, s);
        }
    }

    // ����������
    ~MyString() {
        std::cout << "Destructor called" << std::endl;
        delete[] str;
    }

    // ����������� ����������� (move constructor)
    MyString(MyString&& other) noexcept : str(other.str) {
        std::cout << "Move constructor called" << std::endl;
        other.str = nullptr;
    }

    // �������� ����������� (move assignment)
    MyString& operator=(MyString&& other) noexcept {
        std::cout << "Move assignment operator called" << std::endl;
        if (this != &other) {
            delete[] str;
            str = other.str;
            other.str = nullptr;
        }
        return *this;
    }

    // ����������� �����������
    MyString(const MyString& other) : str(nullptr) {
        std::cout << "Copy constructor called" << std::endl;
        if (other.str != nullptr) {
            str = new char[std::strlen(other.str) + 1];
            std::strcpy(str, other.str);
        }
    }

    // �������� ������������ (copy assignment)
    MyString& operator=(const MyString& other) {
        std::cout << "Copy assignment operator called" << std::endl;
        if (this != &other) {
            delete[] str;
            str = nullptr;
            if (other.str != nullptr) {
                str = new char[std::strlen(other.str) + 1];
                std::strcpy(str, other.str);
            }
        }
        return *this;
    }

    // ����� ��� ������ ������
    void print() const {
        if (str != nullptr) {
            std::cout << str << std::endl;
        }
        else {
            std::cout << "(null)" << std::endl;
        }
    }
};

int main() {
    MyString str1("Hello");
    str1.print();

    // Copy constructor
    MyString str2 = str1;
    str2.print();

    // Move constructor
    MyString str3 = MyString("World");
    str3.print();

    // Copy assignment
    MyString str4;
    str4 = str1;
    str4.print();

    // Move assignment
    MyString str5;
    str5 = MyString("Move");
    str5.print();

    return 0;
}

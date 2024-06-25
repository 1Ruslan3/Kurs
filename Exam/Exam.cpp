#include <iostream>

class Person final 
{
public:
    Person() = default;
    Person(std::string name, unsigned age) : name{ name }, age{ age } {}
    std::string getName() const { return name; }
    unsigned getAge() const { return age; }

    void setName(std::string personName) { name = personName; }
    void setAge(unsigned personAge) { age = personAge; }

public:

    friend std::ostream& operator<<(
	    std::ostream& os,
	    const Person& person)
    {
        return os << person.getName() << " " << person.getAge();
    }

    friend std::istream& operator>>(
        std::istream& in,
        Person& person)
    {
        std::string name;
        unsigned age;
        in >> name >> age;
        person.setAge(age);
        person.setName(name);
        return in;
    }

    Person& operator +=(const Person& right)
    {
        age += right.age;
        return *this;
    }

    Person operator +(Person right) const
    {
        return right += *this;
    }

    bool operator ==(const Person& right) const
    {
        return age == right.age;
    }

    bool operator !=(const Person& right) const
    {
        return !(*this == right);
    }

    bool operator <(const Person& right) const
    {
        return age < right.age;
    }

    bool operator >(const Person& right) const
    {
        return age > right.age;
    }

    Person& operator ++()
    {
        ++age;
        return *this;
    }

    Person operator ++(int)
    {
        Person ret = *this;
        ++*this;
        return ret;
    }

private:
    std::string name;
    unsigned age;
};




int main()
{
    Person number1 = Person("Ruslan", 21);
    Person number2 = Person("Misha", 22);
    Person number3 = number2 + number1;
    bool a = number1 < number2;
    number2++;
    

    std::cout << number2;
    /*std::cout << number1 << std::endl;
    std::cin >> number1;
    std::cout << number1;*/

	return 0;
}
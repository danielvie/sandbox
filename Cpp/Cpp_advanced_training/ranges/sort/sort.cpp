#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

class Person
{
private:
    const char *first_name;
    const char *last_name;
    int length;

public:
    Person(const char *first_name, const char *last_name, int length) : first_name(first_name), last_name(last_name), length(length)
    {
        ;
    }
    int get_length()
    {
        return length;
    }
    void dump()
    {
        std::cout << first_name << " " << last_name << " " << length << std::endl;
    }

    // friend std::ostream& operator<< (std::ostream& stream, const Person& p);

    void operator<<(std::ostream &os) const {
        os << first_name << " " << last_name << " " << length << std::endl;
    }

    // friend std::ostream& operator<<(std::ostream& os, const Person& p)
    // {
    //     os << p.first_name << " " << p.last_name << " " << p.length << std::endl;
    //     return os;
    // }
};

std::ostream &operator<<(std::ostream &os, const Person *p) {
    *p << os;
    return os;
}

int main(int argc, char **argv)
{
    std::vector<Person *> persons;
    persons.push_back(new Person("Franc", "Grootjen", 185));
    persons.push_back(new Person("John", "Smith", 178));
    persons.push_back(new Person("Mary", "Baker", 190));
    persons.push_back(new Person("Eileen", "Runner", 172));
    persons.push_back(new Person("Daisy", "Duck", 175));
    persons.push_back(new Person("Rory", "Gallagar", 167));
    persons.push_back(new Person("Piet", "Hein", 184));
    persons.push_back(new Person("Kevin", "Stout", 192));
    persons.push_back(new Person("Mark", "Rogue", 176));

    // sort here
    std::ranges::sort(persons, {}, &Person::get_length);

    std::ranges::copy(persons, std::ostream_iterator<Person *>(std::cout));

    // std::cout << std::endl;
    // for (Person *p : persons)
    //     p->dump();
}

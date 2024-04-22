// file Person.cpp

#include <iostream>

#include "Person.h"

#include "Swimmer.h"
#include "Programmer.h"
#include "Typist.h"

Person::Person() : name(""), age(0) {}

Person::Person( std::string name_, int age_ ) :
		name(name_), age(age_) {}

Person::~Person() {}

void Person::outputintern(std::ostream& o) const {
	o << name << ' ' << age;
}

void Person::output(std::ostream& o) const {
	o << "Person " ;
        outputintern(o);
}

void Person::input(std::istream& i) {
	i >> name;
	i >> age;
}

std::ostream& operator<<(std::ostream& o, const Person& p) {
	p.output(o);
	return o;
}

std::istream& operator>>(std::istream& i, Person* &p) {
	// ... TJA ...

    std::string s;
    i >> s;
    if (!i) { return i; } // at EOF don't proceed anymore
    if (s == "Person") { p = new Person; }
    if (s == "Swimmer") { p = new Swimmer; }
    if (s == "Programmer") { p = new Programmer; }
    if (s == "Typist") { p = new Typist; }
    p->input(i); // virtual call!

	return i;
}
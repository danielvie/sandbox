#include "Typist.h"
#include <iostream>

Typist::Typist() {}
Typist::Typist(std::string name_, int age_, std::string keyboard_ ) :
	Person(name_,age_), keyboard(keyboard_) {}

Typist::~Typist() {}

void Typist::output(std::ostream& o) const {
	o << "Typist ";
	outputintern(o);
}

void Typist::outputintern(std::ostream& o) const {
	Person::outputintern(o);
	o << ' ';
	o << keyboard;
}

void Typist::input(std::istream& i) {
	Person::input(i);
	i >> keyboard;
}

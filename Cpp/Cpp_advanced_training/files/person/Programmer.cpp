#include "Programmer.h"

#include <iostream>

Programmer::Programmer() {}
Programmer::Programmer(std::string name_, int age_, std::string language_ ) : 
	Person(name_,age_), language(language_) {}

Programmer::~Programmer(){}

void Programmer::outputintern(std::ostream& o) const {
	Person::outputintern(o);
	o << ' ';
	o << language;
}

void Programmer::output(std::ostream& o) const {
	o << "Programmer ";
	outputintern(o);
}

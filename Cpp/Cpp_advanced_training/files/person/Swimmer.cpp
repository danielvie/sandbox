// file Swimmer.cpp

#include <cstring>
#include <iostream>
#include "Swimmer.h"
const char Swimmer::diplomaname[] = { 'A', 'B', 'C', 'D', 'E', 'F' };

Swimmer::Swimmer() : diploma(Diploma::A) {}

Swimmer::Swimmer( std::string name_, int age_,
    Diploma diploma_ ) : 
	Person(name_, age_), diploma(diploma_) {}

Swimmer::~Swimmer() {}

void Swimmer::outputintern(std::ostream& o) const {
	Person::outputintern(o);
	o << ' ';
	o << diplomaname[int(diploma)];
}

void Swimmer::output(std::ostream& o) const {
	o << "Swimmer ";
	outputintern(o);
}

void Swimmer::input(std::istream& i) {
	Person::input(i);

	char helper;
	i >> helper;
		// read Diploma as char

	const char *c;
	if( c = std::strchr(diplomaname, helper) ) {
		diploma = static_cast<Diploma>(helper - 'A');
	}
}

// file Swimmer.h

#ifndef SWIMMER_H
#define SWIMMER_H
#include <iostream>

#include "Person.h"

class Swimmer : public Person {
public:
	enum class Diploma { A, B, C, D, E, F };
	Swimmer();
	Swimmer(std::string name_, int age_,
		Diploma diploma_);
	~Swimmer();

protected:
	static const char diplomaname[];
	void outputintern(std::ostream&) const;
	void output(std::ostream&) const;
	void input(std::istream&);

private:
	Diploma diploma;
};

#endif

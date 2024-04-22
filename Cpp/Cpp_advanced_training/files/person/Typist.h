#ifndef TEXTV_H
#define TEXTV_H

#include <string>

#include "Person.h"

class Typist : public Person {
public:
	Typist( std::string name_, int age_, std::string keyboard_ );
	Typist();
	~Typist();

protected:
	void output(std::ostream& o) const;

	void outputintern(std::ostream& o) const;

	void input(std::istream& i);

private:
	std::string keyboard;
};

#endif 

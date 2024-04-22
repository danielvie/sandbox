#ifndef PROGRAMMER_H
#define PROGRAMMER_H

#include <string>

#include "Person.h"

class Programmer : public Person {
public:
    Programmer();
	Programmer( std::string name_, int age_, std::string language_ );
	~Programmer();

protected:
	void outputintern(std::ostream& o) const;

	void output(std::ostream& o) const;

private:
	std::string language;
};
#endif

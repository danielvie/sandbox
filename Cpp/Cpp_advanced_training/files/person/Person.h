// file Person.h

#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iosfwd>

class Person {
public:
	Person(); 
	Person( std::string name_, int age_ );
	~Person(); 

	friend std::ostream& operator<<(std::ostream& o, const Person& p);
	friend std::istream& operator>>(std::istream& i, Person* &p);

protected:
	virtual void output(std::ostream&) const;
	void outputintern(std::ostream&) const;
	virtual void input(std::istream&);

private:
	std::string name;
	int age;
};
#endif


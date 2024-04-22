#include <iostream>
#include <cstring>

class Str{
public:
	Str(const char* b_) { set(b_); }
	virtual ~Str() { 
		std::cout << "~Str() deleting " << b << std::endl; 
		delete [] b; 
	}
	virtual Str& operator=(const Str& bs) { 
		if( this != &bs) {
			delete [] b; 
			set(bs.b); 
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream&, const Str&);
private:
	void set(const char *b_){
		b = new char[strlen(b_)+1];
		strcpy(b, b_);
	}
protected:
	char *b;
};

std::ostream& operator<<(std::ostream& os, const Str& tekst)
{
	return os << tekst.b;
}

class UpStr : public Str{
public:
	UpStr(const char *b_) : Str(b_) { 
		upper(); 
	}
	~UpStr() { 
		std::cout << "~Upstr() called" << std::endl; 
	}

	UpStr& operator=(const Str& bs){		
		if( this != &bs ) {
			Str::operator=(bs); upper(); } return *this; } void upper() { char
			*p=b; while (*p) { *p=toupper(*p); ++p; } } };


int main()
{
	Str *bp;

	Str   s("AaAaAaAa");
	UpStr u("BbBbBbBb");

	bp = &s; 
	std::cout << *bp << std::endl;		// AaAaAaAa
	bp = &u; 
	std::cout << *bp << std::endl;		// BBBBBBBB

	*bp = s;				// assign s to u
						// (via bp)

	std::cout << *bp << std::endl;		// ????????
	
	return 0;
}

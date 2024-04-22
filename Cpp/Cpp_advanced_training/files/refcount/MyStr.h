#ifndef STRING_HXX
#define STRING_HXX

#include <iostream>
#include <cstring>
#include <string>
// #include <format>

/*
 * class MyStr is like string
 *
 */

class MyStr {
public:

    static int m_Co1;
    static int m_Co2;
    static int m_As1;
    static int m_As2;
    static int n_De;

	friend std::ostream& operator<<(std::ostream&, const MyStr&);
	friend std::istream& operator>>(std::istream&, MyStr&);

	friend bool operator<(const MyStr&, const MyStr&);
	friend bool operator>(const MyStr&, const MyStr&);
	friend bool operator==(const MyStr&, const MyStr&);

	MyStr(const char *ns="") {
		copy(ns);
        m_Co1++;
	}

	MyStr(const MyStr &x) {
		copy(x.s, x.len);
        m_Co2++;
	}

	~MyStr() {
		delete [] s;
        n_De++;
	}

	MyStr& operator=(const char * source) {
		delete [] s;
		copy(source);
        m_As1++;
		return *this;
	}

	MyStr& operator=(const MyStr& source) {
		if(this != &source) {
			delete [] s;
			copy(source.s, source.len);
		}
        m_As2++;
		return *this;
	}

private:

	void copy(const char *ns, int l) {
		len = l;
		s = new char[len+1];
		strcpy(s, ns);
	}

	void copy(const char *ns) {
		copy(ns, strlen(ns));
	}

	char* s;
	int len;

};

inline std::istream& operator>>(std::istream& is, MyStr& tekst)
{
	std::string s;
	is >> s;
	tekst=s.c_str();
	return is;
}

inline std::ostream& operator<<(std::ostream& os, const MyStr& tekst)
{
	os << tekst.s;
	return os;
}

inline bool operator>(const MyStr& l, const MyStr& r) {
	return strcmp(l.s, r.s) > 0;
}

inline bool operator<(const MyStr& l, const MyStr& r) {
	return strcmp(l.s, r.s) < 0;
}

inline bool operator==(const MyStr& l, const MyStr& r) {
	return strcmp(l.s, r.s) == 0;
}
#endif /* STRING_HXX */

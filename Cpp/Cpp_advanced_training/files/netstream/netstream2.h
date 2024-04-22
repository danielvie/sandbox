#ifndef NETSTREAM2_H
#define NETSTREAM2_H
#include <string>
#include <string.h>
#include <iostream>
#include <fstream>

class netstreambuf : public std::streambuf {
public:
	netstreambuf(const std::string& host, const std::string& port);
	netstreambuf(const std::string& host, int);
	~netstreambuf();
	void insert(std::streambuf *);
	void remove(std::streambuf *);

private:
	netstreambuf(const netstreambuf &){} // no copying allowed
public:

	std::streambuf::int_type
    	overflow(traits_type::int_type c=traits_type::eof()) ;
    netstreambuf::traits_type::int_type
        uflow() ; // used in unbuffered situations (like ours)
    netstreambuf::traits_type::int_type
        underflow() ; // used in buffered situations (unlike ours)
private:
    int sock_fd;
    bool takeFromBuf;
    traits_type::char_type charBuf;
};

class netstream2 : public std::iostream {
public:
	netstream2(const std::string& host, const std::string& port);
	netstream2(const std::string& host, int);
	~netstream2();
	void flush();
protected:
	netstreambuf *rdbuf();
};
#endif

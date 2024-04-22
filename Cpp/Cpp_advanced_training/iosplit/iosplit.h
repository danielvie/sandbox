#ifndef METASTREAMBUF_H
#define METASTREAMBUF_H
#include <string>
#include <set>
#include <map>
#include <iostream>

class metastreambuf : public std::basic_streambuf<char> {
    typedef std::basic_streambuf<char> streambuf;
public:
	metastreambuf();
	~metastreambuf();
	void insert(streambuf *);
	void remove(streambuf *);
	std::streamsize xsputn(const traits_type::char_type * s, std::streamsize n);
	int sync();

private:
	metastreambuf(const metastreambuf &){} // no copying allowed
public:
	traits_type::int_type overflow(traits_type::int_type c=traits_type::eof()) ;

private:
	typedef std::set<streambuf *> bufset;
	bufset buffers;
};

class ostreammux : public std::ostream {
public:
	ostreammux();
	~ostreammux();
	void insert(std::ostream &stream, const std::string &tag);
	void remove(const std::string &tag);
	void enable(const std::string &tag);
	void disable(const std::string &tag);

protected:
	metastreambuf *rdbuf();
private:
	typedef std::map<std::string, std::ostream *> streammap;
	streammap streams;
};
#endif

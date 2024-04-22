#include <typeinfo>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "iosplit.h"

using namespace std;

metastreambuf::metastreambuf(){
	setbuf(0, 0); // NO BUFFERING
	cerr << "metastreambuf::metastreambuf()" << endl;
}

metastreambuf::~metastreambuf(){
}

metastreambuf::traits_type::int_type metastreambuf::overflow(traits_type::int_type c) {
	if( !traits_type::eq_int_type(c, traits_type::eof()) ){
		for(bufset::iterator bp = buffers.begin(); bp != buffers.end(); ++bp){
			(*bp)->sputc(c);
		}
		return c;
	} else {
		//return traits_type::not_eof();
        return 1;
	}
}
int metastreambuf::sync(){
	overflow();
	return 0;
}
void metastreambuf::remove(streambuf *b){
	buffers.erase(b);
}
void metastreambuf::insert(streambuf *b){
	buffers.insert(b);
}
streamsize metastreambuf::xsputn(const traits_type::char_type * s, streamsize n){
	cerr << "metastreambuf::xsputn" << "'";
	streamsize x = n;
	const traits_type::char_type *q = s;
	while(x--) cerr.put(*q++);
	cerr << "'" << endl;
	return streambuf::xsputn(s, n);
}

ostreammux::ostreammux():ostream(new metastreambuf){
	cerr << "ostreammux::ostreammux()" << endl;
}

ostreammux::~ostreammux(){
}

metastreambuf * ostreammux::rdbuf(){
	return dynamic_cast<metastreambuf *>(ostream::rdbuf());
}

void ostreammux::insert(ostream &stream, const string &tag){
	streams[tag] = &stream;
	rdbuf()->insert(stream.rdbuf());
}

void ostreammux::remove(const string &tag){
	ostream *stream = streams[tag];
	if(stream){
		rdbuf()->remove(stream->rdbuf());
	}
	streams.erase(tag); // if it wasn't in it will have been added
}

void ostreammux::enable(const string &tag){
	ostream *stream = streams[tag];
	if(stream){
		rdbuf()->insert(stream->rdbuf());
	}
}

void ostreammux::disable(const string &tag){
	ostream *stream = streams[tag];
	if(stream){
		rdbuf()->remove(stream->rdbuf());
	}
}

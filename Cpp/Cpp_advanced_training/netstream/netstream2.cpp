#include <typeinfo>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "netstream2.h"

using namespace std;

static int connect_to(const string& host, const string& service);
static int connect_to(const string& host, int service);

netstreambuf::netstreambuf(const std::string& host, const std::string& port) 
    : sock_fd(connect_to(host, port)), takeFromBuf(false)
{
	setp(0, 0); // NO BUFFERING
	setg(0,0,0);
	cerr << "netstreambuf::netstreambuf(string,string)" << endl;
}
netstreambuf::netstreambuf(const std::string& host, int port_nr)
    : sock_fd(connect_to(host, port_nr)), takeFromBuf(false)
{
	setp(0, 0); // NO BUFFERING
	setg(0,0,0);
	cerr << "netstreambuf::netstreambuf(string,int)" << endl;
}
netstreambuf::~netstreambuf(){
}

netstreambuf::traits_type::int_type
        netstreambuf::overflow(traits_type::int_type c) {
	if(!traits_type::eq_int_type(c, traits_type::eof())) {
		write(sock_fd, &c, 1);
		return c;
	} else {
	//	return traits::not_eof();
		return 1;
	}
}

netstreambuf::traits_type::int_type
        netstreambuf::underflow() { 
    if(takeFromBuf) {
            return traits_type::to_int_type(charBuf);
    }
    else {
        traits_type::char_type c;
        int n = read(sock_fd, &c , 1);
        if(n < 1) {
            return traits_type::eof();
        }
        else {
            takeFromBuf = true;
            charBuf = c;
            return traits_type::to_int_type(charBuf);
        }
    }
}

netstreambuf::traits_type::int_type
        netstreambuf::uflow() { 

        traits_type::int_type c = underflow();
        takeFromBuf = false;

        return c;
}

netstream2::netstream2(const std::string& host, const std::string& port) :
iostream(new netstreambuf (host, port)) {
	cerr << "netstream2::netstream2()" << endl;
}
netstream2::netstream2(const std::string& host, int port_nr) : iostream(new
netstreambuf(host, port_nr)) {
	cerr << "netstream2::netstream2()" << endl;
}
netstream2::~netstream2(){
	flush(); // should not be needed
}
void netstream2::flush(){
	rdbuf()->overflow(EOF); // not needed as well
}

netstreambuf * netstream2::rdbuf(){
	return dynamic_cast<netstreambuf *>(ostream::rdbuf());
}


static int connect_to(const string& host, const string& service){
    struct servent *se;
    se = getservbyname(service.c_str(), "tcp");
    return connect_to(host, ntohs(se->s_port));
}

static int connect_to(const string& host, int service){
    const char *hostname = host.c_str();
	if(hostent *hp = gethostbyname(hostname)){
		int sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock == -1)throw 10;
		sockaddr_in sa;
		memset( (char*)&sa, '\0', sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_port = htons(service);
		memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length);
		if(connect(sock, (sockaddr *)&sa, sizeof(sa)) == -1)throw errno;
		return sock;
	} else {
		throw 8;
	}
}

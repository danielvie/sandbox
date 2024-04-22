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
#include "netstream.h"

static int connect_to(const char * host, int service){
	if(hostent *hp = gethostbyname(host)){
		int sock = socket(PF_INET, SOCK_STREAM, 0);
		if(sock == -1)throw 10;
		sockaddr_in sa;
		memset( (char*)&sa, '\0', sizeof(sa));
		sa.sin_family = AF_INET;
		sa.sin_port = service;
		memcpy((char *)&sa.sin_addr, hp->h_addr, hp->h_length);
		if(connect(sock, (sockaddr *)&sa, sizeof(sa)))throw 11;
		return sock;
	} else {
		throw 8;
	}
}

netstream1::netstream1(const char * host, const char * service){
	if(servent *the_service = getservbyname(service, "tcp")){
		attach(connect_to(host, the_service->s_port));
	} else {
		throw 7;
	}
}

netstream1::netstream1(const char * host, int service){
	attach(connect_to(host, htons(service)));
}
	
netstream1::~netstream1(){
}

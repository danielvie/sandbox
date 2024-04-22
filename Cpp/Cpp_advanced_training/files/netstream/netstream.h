#ifndef NETSTREAM1_H
#define NETSTREAM1_H
#include <string>
#include <iostream>
#include <fstream>

class netstream1 : public std::fstream {
public:
	netstream1(const char *host, int service);
	netstream1(const char *host, const char *service);
	~netstream1();
};

#endif

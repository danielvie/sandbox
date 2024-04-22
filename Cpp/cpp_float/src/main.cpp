#include <iostream>

int main(int argc, char const *argv[])
{

	float a, b, c;
	bool f;

	a = 1.2;
	b = 3.6;
	c = 9.3;
	
	f = ((a + b) + c) == (a + (b + c));

	std::cout << "f: " << f << std::endl;

	std::cout << "-----------------------------------------\n";
	std::cout << "hello\n";
	return 0;
}
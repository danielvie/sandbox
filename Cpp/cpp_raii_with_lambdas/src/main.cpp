#include <iostream>

auto RAII = [ obj = []() 
				{
					struct S {
						S(){ puts("constructor");}
						~S(){ puts("destructor");}
					};
					return S{};
				}()
			] (int value) 
{
	printf("execute: %d\n", value);
};


int main(int argc, char const *argv[])
{
	RAII(5);
	return 0;
}
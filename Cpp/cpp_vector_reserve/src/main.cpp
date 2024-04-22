// vector::reserve
#include <iostream>
#include <vector>

int main()
{
	std::vector<int>::size_type sz;

	// first case: using std::vector
	std::vector<int> foo;
	sz = foo.capacity();
	std::cout << "making foo grow:\n";
	for (int i = 0; i < 100; ++i)
	{
		foo.push_back(i);
		if (sz != foo.capacity())
		{
			sz = foo.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}

	// second case: using std::vector::reserve
	std::vector<int> bar;
	sz = bar.capacity();
	bar.reserve(10); // this is the only difference with foo above
	std::cout << "making bar grow:\n";
	for (int i = 0; i < 801; ++i)
	{
		bar.push_back(i);
		if (sz != bar.capacity())
		{
			sz = bar.capacity();
			std::cout << "capacity changed: " << sz << '\n';
		}
	}
	return 0;
}
#include <iostream>
#include <vector>
#include <span>
#include <numbers>
#include <format>

int main(int argc, char const *argv[])
{
	// Numbers
	double radius = 5.0;	double area = std::numbers::pi * radius * radius;
	std::cout << "Area of a circle with radius " << radius << ": " << area << std::endl;

	// Format
	std::cout << std::format("Area of a circle with radius {}: {}\n", radius, area);

	return 0;
}
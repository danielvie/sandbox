#include <iostream>
#include <memory>
#include <cctype>

// // questao 15 ini
// struct Base {
// 	Base() { f("Base::ctor"); }
// 	virtual ~Base() { f("Base::dtor"); }
	
// 	virtual void f(char const* label) const { std::cout << label << ": Base\n";}
// 	void g() const { return f("Base::g");}
// };

// struct Derived : Base {
// 	Derived() { f("Derived::ctor");}
// 	~Derived() { f("Derived::dtor");}
	
// 	void f(char const* label) const { std::cout << label << ": Derived\n";}
// 	void g() const { return f("Derived::g");}
// };
// // questao 15 fim

// questao 16 ini
template<typename Transformer>
void tranform_and_print(Transformer t, std::string str)
{
	t(str);
	std::cout << str << "\n";
}
// questao 16 fim

// questao 17 ini
// void a(int x) {
// 	x++;
// }

// void b(int* x) {
// 	x += 2;
// }

// void c(int& x) {
// 	x += 4;
// }
// questao 17 fim

// questao 18 ini
// struct Base {
// 	virtual ~Base() = default;
	
// 	virtual void f(char const* label) const { std::cout << label << ": Base\n";}
// 	virtual void g(char const* label) const { std::cout << label << ": Base\n";}
// };

// struct Derived : Base {
// 	void f(char const* label) const { std::cout << label << ": Derived\n";}
// 	void g(char const* label) const { std::cout << label << ": Derived\n";}
// };
// questao 18 fim

struct person {
	std::string name;
	int age;
};

std::ostream& operator<<(std::ostream& os, person const& p) {
	os << p.name << " of age " << p.age;
	return os;
}

std::ostream& operator<<(std::ostream& os, person const& p) {
	std::cout << p.name << " of age " << p.age;
	return os;
}

std::ostream const& daniel<<(std::ostream& os, person const& p) {
	os << p.name << " of age " << p.age;
	return os;
}

void operator<<(std::ostream& os, person const& p) {
	os << p.name << " of age " << p.age;
}

int main(int argc, char const *argv[])
{

	// questao 19
	std::cout << person{"John", 32} << '\n';

	// questao 18
	// Derived d;
	// Base b1 = d;
	// Base& b2 = d;

	// d.f("d.f");
	// d.g("d.g");
	// b1.f("b1.f");
	// b1.g("b1.g");
	// b2.f("b2.f");
	// b2.g("b2.g");


	// questao 15
	// std::unique_ptr<Base> b(new Derived);	
	// b->g();

	// questao 16
	// auto toupper1 = [](auto str) { for (auto c: str) c = std::toupper(c); };
	// auto toupper2 = [](auto& str) { for (auto c: str) c = std::toupper(c); };
	// auto toupper3 = [](auto str) { for (auto& c: str) c = std::toupper(c); };
	// auto toupper4 = [](auto& str) { for (auto& c: str) c = std::toupper(c); };

	// tranform_and_print(toupper1, "toupper1");
	// tranform_and_print(toupper2, "toupper2");
	// tranform_and_print(toupper3, "toupper3");
	// tranform_and_print(toupper4, "toupper4");
	
	// questao 17
	// int x = 0;
	// a(x);
	// b(&x);
	// c(x);
	
	// std::cout << x << "\n";
	

	return 0;
}
#include <iostream>
#include "fraction.h"

using namespace std;

int main() {

	Fraction n(17,4);

	cout << "Fraction: ";
	n.printfraction(cout) << endl;

	cout << "Entirefraction: "; 
	n.printentirefraction(cout) << endl;

	cout << "Float:"; 
	n.printfloat(cout) << endl;

// remove //+ as your design proceeds
//+ cout << "Fraction: " << asfraction << n << endl;
//+ cout << "Entirefraction: " << asentirefraction << n << endl;
//+ cout << "Float:" << asfloat << n << endl;
}

#include <fstream>
#include "iosplit.h"

using namespace std;

int main(){
	ostreammux opgant;
	ofstream Alice("Alice");
	ofstream Bob("Bob");

	opgant.insert(Alice, "first");
	opgant.insert(Bob, "second");

	opgant << "hurray" << endl 
		<< "until here" ;

	opgant.disable("second");
	opgant << endl << "and no further";

	opgant.disable("first");
	opgant.enable("second");
	opgant << "now all other ones" << endl;
	opgant << 'X' << endl;

	return 0;
}

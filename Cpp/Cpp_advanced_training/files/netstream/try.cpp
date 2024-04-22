#include "netstream.h"

using namespace std;

int main ( int argc, char * argv[] ) {
	netstream1 echo("localhost", 7);
	netstream1 echo2("localhost", "finger");
	echo << "Hello" << endl;
	echo2 << "john" << endl;
	string s;
	echo >> s;
	cout << s << endl;
	while(echo2 >> s) cout << s << endl;
	echo2.close();

	return 0;
}

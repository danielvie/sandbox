#include "netstream2.h"

using namespace std;

int main ( int argc, char * argv[] ) {
    try {
        //netstream2 echo("localhost", 7);
        iostream echo(new netstreambuf("localhost", 7));
        netstream2 www("localhost", "http");
        echo << "Hello world!" << endl << flush;
        www << "GET / HTTP/1.0" << endl << endl << flush;
        string s;
        echo >> s;
        cout << s << endl;
        echo >> s;
        cout << s << endl;
        /* This is a possible implementation with a char buffer:
        int bufSize(10);
        char *buf = new char[bufSize];
        while(1) {
            www.getline(buf, bufSize);
            if( www.good() ) {
                cout << buf << endl;
            }
            else if( www.eof() ) {
                break;
            }
            else if( www.fail() ) {
                delete [] buf;
                bufSize *= 2;
                buf = new char[bufSize];
                www.clear();
            }
            else if( www.bad() ) {
                cerr << "Read failed" << endl;
                throw 1;
            }
            else {
                cerr << "Huh, whot?" <<endl;
                throw 1;
            }
        }
        delete [] buf;
        */
        // But a getline(istream&, string&) exists...
        while(getline(www, s)) cout << s << endl;
        // The >> suppresses all white space, not nice..
        //while(www >> s) cout << s << endl;
    }
    catch(int x) {
           cerr << "Oops " << x << "(" << strerror(x) << ")" << endl;
    }
	return 0;
}

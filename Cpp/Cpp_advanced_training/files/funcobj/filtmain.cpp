#include <iostream>
#include <string>

#include "uppercase.h"	// contains class uppercase filter
#include "reverse.h"	// contains class reverse filter

using namespace std;

int main()
{
	string s = "lower case string";
// Remove //+ as your design proceeds
//+	upfilter  up;
//+	revfilter rev;

	string result;

//+	result=up(rev(s));

	cout << result << endl;	// "GNIRTS ESAC REWOL"

//+	result=upfilter()(revfilter()(s));

	cout << result << endl;	// "GNIRTS ESAC REWOL"
	return 0;
}

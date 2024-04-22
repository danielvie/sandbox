#include <iostream>
#include <string>

#include "uppercase.h"	// contains class uppercase filter
#include "reverse.h"	// contains class reverse filter
#include "tr.h"		// contains class tr filter

using namespace std;

int main()
{
	string s = "lower case string";
// Remove //+ as your design proceeds
//+	upfilter  up;
//+	revfilter rev;
//+	trfilter  tr('E', 'X');

	string result;

//+	result = tr(rev(up(s)));

	cout << result << endl;	// "GNIRTS XSAC RXWOL"

//+	result=trfilter('E','X')(upfilter()(revfilter()(s)));

	cout << result << endl;	// "GNIRTS XSAC RXWOL"
	return 0;
}

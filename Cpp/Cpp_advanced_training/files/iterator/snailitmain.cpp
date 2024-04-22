#include <string>
#include <vector>
#include <iostream>
#include "snailiter.h"

using namespace std;

int main() {

  vector<string> v;
  string s;
  typedef vector<string>::iterator viter;

  while (cin >> s) v.push_back(s);

  SnailIter<viter> si(v.begin());


  for (; si!=v.end(); ++si) {
    cout << *si << endl;       // prints everything twice
  }

}

  

#include <string>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include "finditer.h"

using namespace std;

struct prime {
  bool operator()(int n) {
    if (n==0 | n==1) return false;
    if (n%2 == 0) return false;
    int d=3;
    while (n%d && d*d<n) {
      d+=2;
    }
    return d*d > n;
  }
};

int main() {


  vector<int> v;
  string s;
  typedef vector<int>::iterator viter;

  for (int i=0; i<10000; ++i) v.push_back(rand());

  FindIter<viter, prime> fi(v.begin(), v.end(), prime());

  for (; fi!=v.end(); ++fi) {
    cout << *fi << endl;
  }

}

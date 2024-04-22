#include "SkipList.h"
#include <string>

using namespace std;

int main() {

  string s;
  int n;
  SkipList<string, int>shoesize;

  while (cin >> s >> n) {
    shoesize.insert(s, n);
  }

  SkipNode<pair<string, int> > *iter;
  iter=shoesize.begin();
  while (iter != shoesize.end()) {
    cout << iter->get().first << " has size " << iter->get().second << endl;
    iter=iter->next();
  }
  
}

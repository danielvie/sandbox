#include <iostream>
#include "array.h"

int main() {
    using namespace std;

    const Array<int> row(10, 0);
    Array<int> row2(10, 0);

    int i = row[2];
    row2[2] = 0;
    i = row2[2];

    for(i=0;i<10;i++) {
        row2[i] = i; 
    }

    for(i=0;i<10;i++) {
        cout << row2[i]; 
    }

    cout<<endl;
}

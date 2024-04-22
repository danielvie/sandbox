#include <iostream>
#include "sqrefunc2.h"
#include "sum.h"

using namespace std;

// double sqre1(double x) {
// 	return -3*x*x + 5*x + 1;
// }


int main()
{
    // sqre sqrt1;
    
    // cout << sum(sqrt1, -3, +3, 0.000001) << endl;
    // cout << sum(sqrt1, 1, +2, +3) << endl;
    // cout << sum(sqrt1, 2, -2, -1) << endl;
    // cout << sum(sqrt1, -3, -5, +7) << endl;
    // cout << sum(sqrt1, 3, +2, +1) << endl;


    cout << sum(sqre(-3,  5,  1), -3, +3, 0.000001) << endl;
    cout << sum(sqre( 1,  2,  3), -3, +3, 0.000001) << endl;
    cout << sum(sqre( 2, -2, -1), -3, +3, 0.000001) << endl;
    cout << sum(sqre(-3, -5,  7), -3, +3, 0.000001) << endl;
    cout << sum(sqre( 3,  2,  1), -3, +3, 0.000001) << endl;

}
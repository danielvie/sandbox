#include <iostream>
#include "sqrefunc.h"
#include "sum.h"

using namespace std;

double sqre1(double x)
{
    return -3 * x * x + 5 * x + 1;
}

double sqre2(double x)
{
    return 1 * x * x + 2 * x + 3;
}

double sqre3(double x)
{
    return 2 * x * x - 2 * x - 1;
}

double sqre4(double x)
{
    return -3 * x * x - 5 * x + 7;
}

double sqre5(double x)
{
    return 3 * x * x + 2 * x + 1;
}

int main()
{
    cout << sum(sqre1, -3, +3, 0.000001) << endl;
    cout << sum(sqre2, -3, +3, 0.000001) << endl;
    cout << sum(sqre3, -3, +3, 0.000001) << endl;
    cout << sum(sqre4, -3, +3, 0.000001) << endl;
    cout << sum(sqre5, -3, +3, 0.000001) << endl;
}

#include <iostream>
#include "arraypushsafe.h"

using namespace std;

enum seasons {spring, summer, fall, winter };
char *names[] = {
    "spring", "summer", "fall", "winter"
};

int main() {

    Array<seasons> season;  // January=0..December=11

    season.push(winter);
    season.push(winter);
    season.push(spring);
    season.push(spring);

    season.push(spring);
    season.push(summer);
    season.push(summer);
    season.push(summer);

    season.push(fall);
    season.push(fall);
    season.push(fall);
    season.push(winter);

    cout << "via index operator\n";
    for (int month=0; month < 12; month++) {
      cout << "in month number " << month + 1 << " it is " 
           << names[season[month]] << endl;
    }
    cout << endl;

    cout << "via pop and top operations\n";
    for (int month=0; month < 12; month++) {
      cout << "in month number " << month + 1 << " it is " 
           << names[season.pop()] << endl;
    }
}

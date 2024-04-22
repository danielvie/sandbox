#include <iostream>
#include "array.h"

enum seasons {spring, summer, fall, winter };
const char *names[] = {
    "spring", "summer", "fall", "winter"
};

int main() {
    using namespace std;

    Array<seasons> season(12);  // January=0..December=11

    season[0]=winter;
    season[1]=winter;
    season[2]=spring;
    season[3]=spring;

    season[4]=spring;
    season[5]=summer;
    season[6]=summer;
    season[7]=summer;

    season[8]=fall;
    season[9]=fall;
    season[10]=fall;
    season[11]=winter;

    for (int month=0; month < 12; month++) {
      cout << "in month number " << month + 1 << " it is " 
           << names[season[month]] << endl;
    }

}

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

int main()
{
        ifstream file("speech");
        string word;

        map<string, int> frequency;
                // here you'll have the words and
                // the corresponding frequency numbers

        while( file >> word ) {
                frequency[word]++;
        }

        map<string, int>::iterator finger;
        for(finger=frequency.begin(); 
                finger!=frequency.end(); ++finger ) {
            cout << finger->first << " " << 
                finger->second << endl;
        }

        return 0;
}

#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>

#include "MyStr.h"

using namespace std;

class printcounters
{
public:
    ~printcounters()
    {
        cout << "\n\n";
        cout << "char *ns constr: " << MyStr::m_Co1 << std::endl;
        cout << "const MySTr &x const: " << MyStr::m_Co2 << std::endl;
        cout << "operator=(const char *): " << MyStr::m_As1 << std::endl;
        cout << "operator=(const MyStr&): " << MyStr::m_As2 << std::endl;
        cout << "destructor: " << MyStr::n_De << std::endl;
    }
};

int MyStr::m_As1 = 0;
int MyStr::m_As2 = 0;
int MyStr::m_Co1 = 0;
int MyStr::m_Co2 = 0;
int MyStr::n_De = 0;

static printcounters pc;

int main()
{
    vector<MyStr> speech;
    ifstream file("speech");
    MyStr newword;

    while (file >> newword) // read new word from file
    {
        speech.push_back(newword);
        // put it into the vector
    }

    sort(speech.begin(), speech.end());

    copy(speech.begin(), speech.end(),
         ostream_iterator<MyStr>(cout, " "));
    cout << endl;
    return 0;
}
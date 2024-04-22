#include <fstream>

#include "Person.h"
#include "Swimmer.h"
#include "Programmer.h"
#include "Typist.h"



int main()
{
    using namespace std;

    Person *people[4];
    people[0] = new Person("Henry", 70);
    people[1] = new Swimmer("Erica", 55, Swimmer::Diploma::C);
    people[2] = new Programmer("Bjarne", 40, "C++");
    people[3] = new Typist("William", 60, "QWERTY");

    // print Persons to file "database"

    ofstream file("database");
    for (int i = 0; i < 4; ++i)
    {
        file << *people[i] << endl;
    }
    file.close();

    /* and now read it again: */

    // istream& operator>>(istream &i, Person* &p) 
    // {
    //     string s;
    //     i >> s;
    //     if (!i) { return i; } // at EOF don't proceed anymore
    //     if (s == "Person") { p = new Person; }
    //     if (s == "Swimmer") { p = new Swimmer; }
    //     if (s == "Programmer") { p = new Programmer; }
    //     if (s == "Typist") { p = new Typist; }
    //     p->input(i); // virtual call!
    //     return i;
    // }

    // ifstream db("database");
    // Person *p;
    // while (db >> p) {
    //	cout << "Read: " << p << endl;
    //	delete p;
    // }



    // - Make an ifstream, connected to the database file.
    // - Make four objects: Person, Swimmer, Programmer and Typist. Now read the records of Henry, Erica,
    //     Bjarne and William by calling the member function input for each of these four objects. Is each object read
    //     in properly?
    // - Now we add some excitement: enable the statements in personmain that were commented out until now
    // (remove the // ).
    // - Add code that takes care that operator>>:
    //     1. Creates an object of the proper type, and
    //     2. reads the object via input().
    // Note: this can be implemented with all corners cut, or you can create a full blown implementation. You are
    //     free to pick your choice.
    // Note that all lines in the database start with the name of the class.


}

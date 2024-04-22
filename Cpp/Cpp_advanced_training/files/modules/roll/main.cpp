#include <iostream>
import roll;
int main(int argc, char **argv)
{
// create a 6 sided die
  roll::Die first(6);
  std::cout << "single die: " << first.roll() << std::endl;
#if 0
  roll::Die second(6);
// create a set of two 6 sided dice
  roll::DieSet pair;
  pair.add(first);
  pair.add(second);
  std::cout << "set of 2 dice: ";
  for(int i=0;i<10;i++)
    std::cout << pair.roll() << " ";
  std::cout << std::endl;
#endif
}

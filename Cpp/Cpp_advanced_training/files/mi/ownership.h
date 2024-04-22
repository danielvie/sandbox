#ifndef OWNERSHIP_H
#define OWNERSHIP_H
#include <iostream>

class Ownership {
public:
  Ownership() {}
  Ownership(std::string own, double pr) : owner(own), price(pr) {}
  void print(std::ostream& os) {
    os << owner << ' ' << price;
  }

private:
  std::string owner;
  double price;
};
#endif

#ifndef CATERING_H
#define CATERING_H
#include <iostream>
#include <string>
#include <map>

class Catering {
public:
  Catering() {}
  Catering(std::string n) : name(n) {}
  void print(std::ostream& os) {
    os << ' ' << name << " pricelist on request";
  }

private:
  std::map<std::string, double> pricelist;
  std::string name;
};
#endif

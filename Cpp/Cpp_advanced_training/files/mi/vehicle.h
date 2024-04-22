#ifndef VEHICLE_H
#define VEHICLE_H
#include <iostream>

class Vehicle {
public:
  Vehicle() : nwheels(0), weight(0) {}
  Vehicle(int nw, double wght) : nwheels(nw), weight(wght) {}
  void print(std::ostream& os) {
    os << ' ' << nwheels << ' ' << weight;
  }

private:
  int nwheels;
  double weight;
};
#endif

#ifndef FOODTRUCK1_H
#define FOODTRUCK1_H
#include <iostream>
#include <string>
#include <map>
#include "vehicle.h"
#include "catering.h"

class FoodTruck : public Vehicle, public Catering {
public:
  FoodTruck() {}
  FoodTruck(int nw, double wght, std::string nm) :  
                       Vehicle(nw, wght), Catering(nm) {}

  void print(std::ostream& os) {
    Catering::print(os);
    Vehicle::print(os);
    os << " timetable on request";
  }


private:
  std::map<std::string, std::pair<int, int> > timetable;
};
#endif

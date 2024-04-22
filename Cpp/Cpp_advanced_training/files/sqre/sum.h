#ifndef SUM_H
#define SUM_H

inline double sum(sqre k, double from, double to, double step) {
  double thesum=0.0;
  for (double x=from; x<to; x+=step) {
    thesum += k(x);
  }
  return thesum * step;
}

#endif

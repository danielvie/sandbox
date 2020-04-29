#if !defined(__UTILS__)
#define __UTILS__

#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/arrayscalars.h>
#include <numpy/numpyconfig.h>

#include <cstdio>

PyArrayObject* create_pyarray(double data[], int len);

#endif // __UTILS__

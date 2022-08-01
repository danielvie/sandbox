#if !defined(__UTILS__)
#define __UTILS__

#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/arrayscalars.h>
#include <numpy/numpyconfig.h>

#include <cstdio>
#include <vector>
#include <string>

PyArrayObject* create_pyarray(double data[], int len);
std::vector<double> get_vetor_double(PyObject* array);

#endif // __UTILS__

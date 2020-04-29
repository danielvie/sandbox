#include "utils.h"

static int init_numpy ( ) {
  NUMPY_IMPORT_ARRAY_RETVAL;
  import_array1(0);
  return 1;
}

const static int numpy_initialized = init_numpy ( );

PyArrayObject* create_pyarray(double data[], int len) {
    int ndims = 1;
    npy_intp dims[1] = {len};
    PyArrayObject *array = (PyArrayObject *)PyArray_SimpleNew(ndims, dims, NPY_DOUBLE);
    memcpy(PyArray_DATA(array), data, sizeof(double) * len);

    return array;
}

std::vector<double> get_vetor_double(PyObject* array) {
    PyObject* item;
    int seqlen;
    int i;

    std::vector<double> array_o;

    /* conferencia se array eh iteravel */
    array = PySequence_Fast(array, "argument must be iterable");

    /* prepare data as an array of doubles */
    seqlen = PySequence_Fast_GET_SIZE(array);

    double valor;
    for (i = 0; i < seqlen; i++) {
        item = PySequence_Fast_GET_ITEM(array, i);
        valor = PyFloat_AsDouble(item);
        array_o.push_back(valor);
    }

    return array_o;
}
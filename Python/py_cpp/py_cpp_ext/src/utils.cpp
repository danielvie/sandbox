#include "utils.h"

void print_utils(void){
    printf("---------------------------\n");
    printf("entrei em utils\n");
    printf("---------------------------\n");
}

static int init_numpy ( ) {
  NUMPY_IMPORT_ARRAY_RETVAL;
  import_array1(0);
  return 1;
}

const static int numpy_initialized = init_numpy ( );

PyArrayObject* create_pyarray(double data[], int len) {
    // FIXME: compilar a biblioteca em python 3.7 e conferir se os vetores continuam funcionando normalmente

    // import_array();
    int ndims = 1;
    npy_intp dims[1] = {len};
    PyArrayObject *array = (PyArrayObject *)PyArray_SimpleNew(ndims, dims, NPY_DOUBLE);
    memcpy(PyArray_DATA(array), data, sizeof(double) * len);

    return array;
}

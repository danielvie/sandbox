/* *veto *set_gravar(PyObject* self, PyObject* args) {
 *  Created on: 13 de dez de 2018
 *      Author: dvieira
 */

// #define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include <Python.h>

#include <numpy/arrayobject.h>
#include <numpy/arrayscalars.h>
#include <numpy/numpyconfig.h>

#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <vector>

#include <iostream>
#include <string>

#include <time.h>

/* DECLARACAO OBJETO NOVAEDT */


/* 
 * PROTOTIPAGEM FUNCOES AUXILIARES 
 * 
 * */


/* 
 * PROTOTIPAGEM METODOS EXTENSAO 
 * 
 * */


PyObject* vetor_grande(PyObject* self, PyObject* args);
PyObject* vetor(PyObject* self, PyObject* args);
PyObject* vetor_n(PyObject* self, PyObject* args);
PyObject* get(PyObject* self, PyObject* args);
PyObject* add(PyObject* self, PyObject* args);

/* 
 * DEFINICAO METODOS EXTENSAO 
 * 
 * */

PyMethodDef SpamMethods[] = {
    // {"vetor_grande", (PyCFunction)vetor_grande, METH_VARARGS, 0},
    {"get", (PyCFunction)get, METH_VARARGS, 0},
    {"add", (PyCFunction)add, METH_VARARGS, 0},
    {"vetor_grande", (PyCFunction)vetor_grande, METH_VARARGS, 0},
    {"vetor", (PyCFunction)vetor, METH_VARARGS, 0},
    {"vetor_n", (PyCFunction)vetor_n, METH_VARARGS, 0},
    {0, 0, 0, 0}};

/* 
 * REGISTRO EXTENSAO PYTHON
 * 
 * */

static struct PyModuleDef extensionmodule = {
    PyModuleDef_HEAD_INIT,
    "extension",
    "Modulo de simulacao programa novaEDT",
    -1,
    SpamMethods};

/* INICIALIZACAO EXTENSAO PYTHON */

PyMODINIT_FUNC PyInit_extension(void) {
    _import_array();
    return PyModule_Create(&extensionmodule);
}

/* METODOS */
PyArrayObject* create_nparray_double(double data[], int len) {
    
    int ndims = 1;
    npy_intp dims[1] = {len};
    
    PyArrayObject *array = (PyArrayObject*)PyArray_SimpleNew(ndims, dims, NPY_DOUBLE);
    memcpy(PyArray_DATA(array), data, sizeof(double) * len);
    // PyObject* np_array = PyArray_SimpleNewFromData(ndims, dims, NPY_DOUBLE, data);

    return array;
}

PyObject* vetor(PyObject* self, PyObject* args) {
    
    std::map<std::string, std::vector<double> > out;
    int i;
    int max = 20;

    for (i = 0; i < max; i++) {
        out["t"].push_back((double)i);        
    }

    int len = out["t"].size();
    printf("len: %d\n", len);

    return Py_BuildValue("N", create_nparray_double(out["t"].data(), len));
}

PyObject* vetor_n(PyObject* self, PyObject* args) {
    
    std::map<std::string, std::vector<double> > out;
    int i;
    int max;

    if (!PyArg_ParseTuple(args, "i", &max)) {
        return NULL;
    }

    for (i = 0; i < max; i++) {
        out["t"].push_back((double)i);        
    }

    int len = out["t"].size();
    printf("len: %d\n", len);

    return Py_BuildValue("N", create_nparray_double(out["t"].data(), len));
}

PyObject* vetor_grande(PyObject* self, PyObject* args) {
    //
    
    std::map<std::string, std::vector<double> > out;
    int i;
    int max = 20;

    for (i = 0; i < max; i++) {
        out["t"].push_back((double)i);        
    }

    int len = out["t"].size();
    printf("len: %d\n", len);

    // ======================================================== 
    int ndims = 1;
    npy_intp dims[1] = {len};
    PyArrayObject *array = (PyArrayObject*)PyArray_SimpleNew(ndims, dims, NPY_DOUBLE);

    memcpy(PyArray_DATA(array), out["t"].data(), sizeof(double) * len);

    return Py_BuildValue("N", array);
}

PyObject* get(PyObject* self, PyObject* args) {
        
    return Py_BuildValue("d", 5.0);
}

PyObject* add(PyObject* self, PyObject* args) {
    
    double a, b;

    if (!PyArg_ParseTuple(args, "dd", &a, &b)) {
        return NULL;
    }
    
    printf("a: %f, b: %f\n", a, b);
    return Py_BuildValue("d", a + b);
}
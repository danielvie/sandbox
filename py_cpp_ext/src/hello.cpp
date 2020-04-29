#include <Python.h>
#include <numpy/arrayobject.h>
#include <numpy/arrayscalars.h>
#include <numpy/numpyconfig.h>

#include <vector>
#include "utils.h"

/* METHODS CALLS */
static PyObject* get_vetor(PyObject *self, PyObject *args);
static PyObject* send_vetor(PyObject *self, PyObject *args);
static PyObject* soma(PyObject *self, PyObject *args);


static PyMethodDef hello_methods[] = {
        {"get_vetor", get_vetor, METH_VARARGS,"numpy function tester",},
        {"send_vetor", send_vetor, METH_VARARGS,"numpy function tester",},
        {"soma", soma, METH_VARARGS,"numpy function tester",},
        {NULL, NULL, 0, NULL}
};

/* MODULE */
static struct PyModuleDef hello_definition = {
        PyModuleDef_HEAD_INIT,
        "hello",
        "A Python module that prints 'hello world' from C code.",
        -1,
        hello_methods
};

/* INIT MODULE */
PyMODINIT_FUNC PyInit_hello(void) {
    Py_Initialize();

    PyObject *m = PyModule_Create(&hello_definition);
    return m;
}

// METHODS
static PyObject* get_vetor(PyObject *self, PyObject *args) {
    /* RETURNING VALUE OF 'a' */
    std::vector<double> bla;
    int len;
    
    if (!PyArg_ParseTuple(args, "i", &len)){
        return NULL;
    }

    for (int i = 0; i < len; i++){
        bla.push_back((double)i);
    }
        
    return Py_BuildValue("O", create_pyarray(bla.data(), len));
}

static PyObject* send_vetor(PyObject *self, PyObject *args) {
    /* RETURNING VALUE OF 'a' */
    
    std::vector<double> bla;
    PyObject *value;

    if (!PyArg_ParseTuple(args, "O", &value)){
        return NULL;
    }

    bla = get_vetor_double(value);

    std::vector<double>::iterator it;
    
    printf("\nIMPRIMINDO VETOR ENVIADO:\n");
    for(it = bla.begin(); it != bla.end(); it++) {
        printf("%f\n", *it);
    }
    printf("\nfim IMPRIMINDO VETOR ENVIADO:\n");

    
    return Py_BuildValue("");
}

static PyObject* soma(PyObject *self, PyObject *args) {
    
    float a, b;
    float value;
    if (!PyArg_ParseTuple(args, "ff", &a, &b))
        return NULL;
    
    return Py_BuildValue("f", a+b);

}
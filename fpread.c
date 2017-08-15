#include <Python.h>

#include <stdio.h>

#ifdef _MSC_VER
#pragma fenv_access (on)
#endif

PyObject *get_control87(PyObject *self, PyObject *args)
{
    unsigned int result;

    if (!PyArg_ParseTuple(args, "")) {
        return NULL;
    }

#ifdef _MSC_VER
    result = _control87(0, 0);
#else
#error Needs MSVC
#endif

    return PyLong_FromLongLong(result);
}

static struct PyMethodDef methods[] = {
    {"_control87", get_control87, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};


static int init_constants(PyObject *m)
{
    PyObject *d;
    PyObject *v;

    d = PyModule_GetDict(m);
    if (d == NULL) {
        return -1;
    }

    v = PyLong_FromLongLong(_MCW_PC);
    if (v == NULL) {
        return -1;
    }

    return PyDict_SetItemString(d, "_MCW_PC", v);
}


#if PY_MAJOR_VERSION >= 3

static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "fpread",
    NULL,
    -1,
    methods,
    NULL,
    NULL,
    NULL,
    NULL
};

PyObject *PyInit_fpread(void)
{
    PyObject *m;

    m = PyModule_Create(&moduledef);
    if (m == NULL) {
        return NULL;
    }

    if (init_constants(m) != 0) {
        Py_DECREF(m);
        return NULL;
    }

    return m;
}

#else

PyMODINIT_FUNC init_fpread(void)
{
    PyObject *m;

    m = Py_InitModule("fpread", methods);
    if (m == NULL) {
        return;
    }

    init_constants(m);
}

#endif

/*
 * Python 3 Bindings for Divi Quark Hash
 * 
 * Provides a single function: getPoWHash(bytes) -> bytes
 * 
 * Example:
 *   >>> import divi_quark_hash
 *   >>> header = bytes.fromhex('...')  # 80-byte block header
 *   >>> pow_hash = divi_quark_hash.getPoWHash(header)
 * 
 * Originally written by @chaeplin, adapted for PIVX by @gpdionisio
 * Re-envisioned and maintained for Divi by @7h3v01c3
 * 
 * MIT License
 */

/* Required for Python 3.10+ when using '#' format specifiers */
#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "quark/quark.h"

PyDoc_STRVAR(module_doc,
    "Divi Quark hash for proof-of-work verification.\n"
    "\n"
    "This module provides the Quark hash function used in Divi's\n"
    "proof-of-work consensus mechanism.\n"
    "\n"
    "Example:\n"
    "    >>> import divi_quark_hash\n"
    "    >>> header = bytes.fromhex('...')  # 80-byte block header\n"
    "    >>> pow_hash = divi_quark_hash.getPoWHash(header)\n"
    "\n"
    "Credits:\n"
    "  - Originally written by @chaeplin\n"
    "  - Maintained by @gpdionisio and others\n"
    "  - Refactored for Divi by @7h3v01c3\n"
);

PyDoc_STRVAR(getpowhash_doc,
    "getPoWHash(header) -> bytes\n"
    "\n"
    "Compute the Quark proof-of-work hash of a block header.\n"
    "\n"
    "Args:\n"
    "    header: A bytes object containing the 80-byte block header.\n"
    "\n"
    "Returns:\n"
    "    A 32-byte bytes object containing the hash result.\n"
    "\n"
    "Raises:\n"
    "    TypeError: If header is not a bytes object.\n"
);

static PyObject *
quark_getpowhash(PyObject *self, PyObject *args)
{
    PyBytesObject *input;
    char *output;
    PyObject *result;

    /* Parse arguments - expects a bytes object */
    if (!PyArg_ParseTuple(args, "S", &input)) {
        return NULL;
    }

    /* Increment reference count while we work with the input */
    Py_INCREF(input);
    
    /* Allocate output buffer */
    output = PyMem_Malloc(QUARK_DIGEST_SIZE);
    if (output == NULL) {
        Py_DECREF(input);
        return PyErr_NoMemory();
    }

    /* Compute the hash */
    quark_hash(PyBytes_AS_STRING((PyObject *)input), output);

    /* Release input reference */
    Py_DECREF(input);

    /* Build return value as bytes object */
    result = Py_BuildValue("y#", output, QUARK_DIGEST_SIZE);
    
    /* Free output buffer */
    PyMem_Free(output);

    return result;
}

/* Method table */
static PyMethodDef quark_methods[] = {
    {"getPoWHash", quark_getpowhash, METH_VARARGS, getpowhash_doc},
    {NULL, NULL, 0, NULL}
};

/* Module definition */
static struct PyModuleDef quark_module = {
    PyModuleDef_HEAD_INIT,
    .m_name = "divi_quark_hash",
    .m_doc = module_doc,
    .m_size = -1,
    .m_methods = quark_methods,
};

/* Module initialization function */
PyMODINIT_FUNC
PyInit_divi_quark_hash(void)
{
    return PyModule_Create(&quark_module);
}

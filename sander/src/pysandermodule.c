/* Python interface to sander functionality */

// Python includes
#include <Python.h>
#include "structmember.h"

// Standard C includes
#include <stdio.h>
#include <string.h>

// Amber-specific includes
#include "sander.h"

// Cordion off the type definitions, since they are large
#include "pysandermoduletypes.c"

/* sander can only be set up once, and must be cleaned up before being set up
 * again. Use this module-level variable to track whether an active system is
 * set up (0 means no system is currently set up, 1 means a system is currently
 * set up). You can only get energies and forces for a system that is set up,
 * you can only clean up a system that is set up, and you can only run setup
 * when a system is not already set up.
 */
static int IS_SETUP = 0;

/* Sander setup routine -- sets up a calculation to run with the given prmtop
 * file, inpcrd file, and input options. */
static PyObject*
pysander_setup(PyObject *self, PyObject *args) {

    char *prmtop, *inpcrd;
    PyObject *arg3, *arg4;
    arg3 = NULL; arg4 = NULL;

    sander_input input;
    qmmm_input_options qm_input;

    // The passed arguments
    if (!PyArg_ParseTuple(args, "ssO|O", &prmtop, &inpcrd, &arg3, &arg4))
        return NULL;

    if (IS_SETUP) {
        // Raise a RuntimeError
        PyErr_SetString(PyExc_RuntimeError,
                        "A sander system is already set up!");
        return NULL;
    }

    pysander_InputOptions *mm_inp;
    mm_inp = (pysander_InputOptions *) arg3;

    // Copy over values from mm_inp to input
    input.igb = (int) PyInt_AS_LONG(mm_inp->igb);
    input.alpb = (int) PyInt_AS_LONG(mm_inp->alpb);
    input.gbsa = (int) PyInt_AS_LONG(mm_inp->gbsa);
    input.lj1264 = (int) PyInt_AS_LONG(mm_inp->lj1264);
    input.ipb = (int) PyInt_AS_LONG(mm_inp->ipb);
    input.inp = (int) PyInt_AS_LONG(mm_inp->inp);
    input.vdwmeth = (int) PyInt_AS_LONG(mm_inp->vdwmeth);
    input.ntb = (int) PyInt_AS_LONG(mm_inp->ntb);
    input.ifqnt = (int) PyInt_AS_LONG(mm_inp->ifqnt);

    input.extdiel = PyFloat_AS_DOUBLE(mm_inp->extdiel);
    input.intdiel = PyFloat_AS_DOUBLE(mm_inp->intdiel);
    input.rgbmax = PyFloat_AS_DOUBLE(mm_inp->rgbmax);
    input.saltcon = PyFloat_AS_DOUBLE(mm_inp->saltcon);
    input.cut = PyFloat_AS_DOUBLE(mm_inp->cut);
    input.dielc = PyFloat_AS_DOUBLE(mm_inp->dielc);

    sander_setup(prmtop, inpcrd, &input, &qm_input);
    IS_SETUP = 1;

    Py_RETURN_NONE;
}

/* Deallocates the memory used by sander so sander can be set up and used again
 */
static PyObject*
pysander_cleanup(PyObject *self) {
    if (!IS_SETUP) {
        // Raise a RuntimeError
        PyErr_SetString(PyExc_RuntimeError,
                        "No sander system is currently set up!");
        return NULL;
    }
    sander_cleanup();
    IS_SETUP = 0;
    Py_RETURN_NONE;
}

/* Creates an input option struct with all of the options optimized for gas
 * phase or implicit solvent (i.e., aperiodic) calculations
 */
static PyObject*
pysander_gas_input(PyObject *self, PyObject *args) {

    int igb = 0;
    if (!PyArg_ParseTuple(args, "|i", &igb)) {
        return NULL;
    }
    sander_input inp;
    gas_sander_input(&inp, &igb);
    pysander_InputOptions *ret = (pysander_InputOptions *)
            PyObject_CallObject((PyObject *) &pysander_InputOptionsType, NULL);
    if (ret == NULL)
        return NULL;
    // Integers
    ret->igb = PyInt_FromLong(inp.igb);
    ret->alpb = PyInt_FromLong(inp.alpb);
    ret->gbsa = PyInt_FromLong(inp.gbsa);
    ret->lj1264 = PyInt_FromLong(inp.lj1264);
    ret->ipb = PyInt_FromLong(inp.ipb);
    ret->inp = PyInt_FromLong(inp.inp);
    ret->vdwmeth = PyInt_FromLong(inp.vdwmeth);
    ret->ntb = PyInt_FromLong(inp.ntb);
    ret->ifqnt = PyInt_FromLong(inp.ifqnt);
    // Floats
    ret->extdiel = PyFloat_FromDouble(inp.extdiel);
    ret->intdiel = PyFloat_FromDouble(inp.intdiel);
    ret->rgbmax = PyFloat_FromDouble(inp.rgbmax);
    ret->saltcon = PyFloat_FromDouble(inp.saltcon);
    ret->cut = PyFloat_FromDouble(inp.cut);
    ret->dielc = PyFloat_FromDouble(inp.dielc);

    return (PyObject *) ret;
}

/* Creates an input option struct with all of the options optimized for PME
 * calculations
 */
static PyObject *
pysander_pme_input(PyObject *self) {
    sander_input inp;
    pme_sander_input(&inp);
    pysander_InputOptions *ret = (pysander_InputOptions *)
            PyObject_CallObject((PyObject *) &pysander_InputOptionsType, NULL);
    if (ret == NULL)
        return NULL;
    // Integers
    ret->igb = PyInt_FromLong(inp.igb);
    ret->alpb = PyInt_FromLong(inp.alpb);
    ret->gbsa = PyInt_FromLong(inp.gbsa);
    ret->lj1264 = PyInt_FromLong(inp.lj1264);
    ret->ipb = PyInt_FromLong(inp.ipb);
    ret->inp = PyInt_FromLong(inp.inp);
    ret->vdwmeth = PyInt_FromLong(inp.vdwmeth);
    ret->ntb = PyInt_FromLong(inp.ntb);
    ret->ifqnt = PyInt_FromLong(inp.ifqnt);
    // Floats
    ret->extdiel = PyFloat_FromDouble(inp.extdiel);
    ret->intdiel = PyFloat_FromDouble(inp.intdiel);
    ret->rgbmax = PyFloat_FromDouble(inp.rgbmax);
    ret->saltcon = PyFloat_FromDouble(inp.saltcon);
    ret->cut = PyFloat_FromDouble(inp.cut);
    ret->dielc = PyFloat_FromDouble(inp.dielc);

    return (PyObject *) ret;
}

/* Python module initialization */

static PyMethodDef
pysanderMethods[] = {
    { "setup", (PyCFunction) pysander_setup, METH_VARARGS,
            "Sets up sander calc"},
    { "cleanup", (PyCFunction) pysander_cleanup, METH_NOARGS,
            "Cleans up sander calc"},
    { "gas_input", (PyCFunction) pysander_gas_input, METH_VARARGS,
            "Returns a populated InputOptions instance optimized for gas-phase\n"
            "or implicit solvent calculations. Optional argument is the GB model\n"
            "you wish to use (1, 2, 5, 7, or 8)"},
    { "pme_input", (PyCFunction) pysander_pme_input, METH_NOARGS,
            "Returns a populated InputOptions instance optimized with Amber\n"
            "defaults for PME calculations.\n"},
#if 0
    { "energy_forces", (PyCFunction) pysander_energy_forces, METH_NOARGS,
            "Returns a populated SanderEnergy instance and a 3*natom-length\n"
            "list of forces."},
#endif
    {NULL}, // sentinel
};

#if PY_MAJOR_VERSION >= 3
static struct PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,
    "pysander",                                                 // m_name
    "Python interface into sander energy and force evaluation", // m_doc
    -1,                                                         // m_size
    pysanderMethods,                                            // m_methods
    NULL,
    NULL,
    NULL,
    NULL,
};
#endif

void initpysander() {
#if PY_MAJOR_VERSION >= 3
    PyModule_Create(&moduledef);
#else
    PyObject *m;
    // Type declarations
    if (PyType_Ready(&pysander_InputOptionsType))
        return;
    if (PyType_Ready(&pysander_EnergyTermsType))
        return;

    // Initialize the module
    m = Py_InitModule3("pysander", pysanderMethods,
                "Python interface into sander energy and force evaluation");

    // Now add the types
    Py_INCREF(&pysander_InputOptionsType);
    PyModule_AddObject(m, "InputOptions", (PyObject*) &pysander_InputOptionsType);
    Py_INCREF(&pysander_EnergyTermsType);
    PyModule_AddObject(m, "EnergyTerms", (PyObject *) &pysander_EnergyTermsType);
#endif
}

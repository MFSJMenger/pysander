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
    pysander_QmInputOptions *qm_inp;

    if (!PyObject_TypeCheck(arg3, &pysander_InputOptionsType)) {
        PyErr_SetString(PyExc_TypeError,
                        "3rd argument must be of type InputOptions");
        return NULL;
    }

    if (arg4 && !PyObject_TypeCheck(arg4, &pysander_QmInputOptionsType)) {
        PyErr_SetString(PyExc_TypeError,
                        "4th argument must be of type QmInputOptions");
        return NULL;
    }

    mm_inp = (pysander_InputOptions *) arg3;

    // Copy over values from mm_inp to input
    input.igb = (int) PyInt_AsLong(mm_inp->igb);
    input.alpb = (int) PyInt_AsLong(mm_inp->alpb);
    input.gbsa = (int) PyInt_AsLong(mm_inp->gbsa);
    input.lj1264 = (int) PyInt_AsLong(mm_inp->lj1264);
    input.ipb = (int) PyInt_AsLong(mm_inp->ipb);
    input.inp = (int) PyInt_AsLong(mm_inp->inp);
    input.vdwmeth = (int) PyInt_AsLong(mm_inp->vdwmeth);
    input.ntb = (int) PyInt_AsLong(mm_inp->ntb);
    input.ifqnt = (int) PyInt_AsLong(mm_inp->ifqnt);
    input.jfastw = (int) PyInt_AsLong(mm_inp->jfastw);

    input.extdiel = PyFloat_AsDouble(mm_inp->extdiel);
    input.intdiel = PyFloat_AsDouble(mm_inp->intdiel);
    input.rgbmax = PyFloat_AsDouble(mm_inp->rgbmax);
    input.saltcon = PyFloat_AsDouble(mm_inp->saltcon);
    input.cut = PyFloat_AsDouble(mm_inp->cut);
    input.dielc = PyFloat_AsDouble(mm_inp->dielc);

    if (arg4) {
        qm_inp = (pysander_QmInputOptions *) arg4;
        // Copy over values from qm_inp to qm_input
        qm_input.qmgb = (int) PyInt_AsLong(qm_inp->qmgb);
        qm_input.lnk_atomic_no = (int) PyInt_AsLong(qm_inp->lnk_atomic_no);
        qm_input.ndiis_matrices = (int) PyInt_AsLong(qm_inp->ndiis_matrices);
        qm_input.ndiis_attempts = (int) PyInt_AsLong(qm_inp->ndiis_attempts);
        qm_input.lnk_method = (int) PyInt_AsLong(qm_inp->lnk_method);
        qm_input.qmcharge = (int) PyInt_AsLong(qm_inp->qmcharge);
        qm_input.corecharge = (int) PyInt_AsLong(qm_inp->corecharge);
        qm_input.buffercharge = (int) PyInt_AsLong(qm_inp->buffercharge);
        qm_input.spin = (int) PyInt_AsLong(qm_inp->spin);
        qm_input.qmqmdx = (int) PyInt_AsLong(qm_inp->qmqmdx);
        qm_input.verbosity = (int) PyInt_AsLong(qm_inp->verbosity);
        qm_input.printcharges = (int) PyInt_AsLong(qm_inp->printcharges);
        qm_input.printdipole = (int) PyInt_AsLong(qm_inp->printdipole);
        qm_input.print_eigenvalues = (int) PyInt_AsLong(qm_inp->print_eigenvalues);
        qm_input.peptide_corr = (int) PyInt_AsLong(qm_inp->peptide_corr);
        qm_input.itrmax = (int) PyInt_AsLong(qm_inp->itrmax);
        qm_input.printbondorders = (int) PyInt_AsLong(qm_inp->printbondorders);
        qm_input.qmshake = (int) PyInt_AsLong(qm_inp->qmshake);
        qm_input.qmmmrij_incore = (int) PyInt_AsLong(qm_inp->qmmmrij_incore);
        qm_input.qmqm_erep_incore = (int) PyInt_AsLong(qm_inp->qmqm_erep_incore);
        qm_input.pseudo_diag = (int) PyInt_AsLong(qm_inp->pseudo_diag);
        qm_input.qm_ewald = (int) PyInt_AsLong(qm_inp->qm_ewald);
        qm_input.qm_pme = (int) PyInt_AsLong(qm_inp->qm_pme);
        qm_input.kmaxqx = (int) PyInt_AsLong(qm_inp->kmaxqx);
        qm_input.kmaxqy = (int) PyInt_AsLong(qm_inp->kmaxqy);
        qm_input.kmaxqz = (int) PyInt_AsLong(qm_inp->kmaxqz);
        qm_input.ksqmaxq = (int) PyInt_AsLong(qm_inp->ksqmaxq);
        qm_input.qmmm_int = (int) PyInt_AsLong(qm_inp->qmmm_int);
        qm_input.adjust_q = (int) PyInt_AsLong(qm_inp->adjust_q);
        qm_input.tight_p_conv = (int) PyInt_AsLong(qm_inp->tight_p_conv);
        qm_input.diag_routine = (int) PyInt_AsLong(qm_inp->diag_routine);
        qm_input.density_predict = (int) PyInt_AsLong(qm_inp->density_predict);
        qm_input.fock_predict = (int) PyInt_AsLong(qm_inp->fock_predict);
        qm_input.vsolv = (int) PyInt_AsLong(qm_inp->vsolv);
        qm_input.dftb_maxiter = (int) PyInt_AsLong(qm_inp->dftb_maxiter);
        qm_input.dftb_disper = (int) PyInt_AsLong(qm_inp->dftb_disper);
        qm_input.dftb_chg = (int) PyInt_AsLong(qm_inp->dftb_chg);
        qm_input.abfqmmm = (int) PyInt_AsLong(qm_inp->abfqmmm);
        qm_input.hot_spot = (int) PyInt_AsLong(qm_inp->hot_spot);
        qm_input.qmmm_switch = (int) PyInt_AsLong(qm_inp->qmmm_switch);

        qm_input.qmcut = PyFloat_AsDouble(qm_inp->qmcut);
        qm_input.lnk_dis = PyFloat_AsDouble(qm_inp->lnk_dis);
        qm_input.scfconv = PyFloat_AsDouble(qm_inp->scfconv);
        qm_input.errconv = PyFloat_AsDouble(qm_inp->errconv);
        qm_input.dftb_telec = PyFloat_AsDouble(qm_inp->dftb_telec);
        qm_input.dftb_telec_step = PyFloat_AsDouble(qm_inp->dftb_telec_step);
        qm_input.fockp_d1 = PyFloat_AsDouble(qm_inp->fockp_d1);
        qm_input.fockp_d2 = PyFloat_AsDouble(qm_inp->fockp_d2);
        qm_input.fockp_d3 = PyFloat_AsDouble(qm_inp->fockp_d3);
        qm_input.fockp_d4 = PyFloat_AsDouble(qm_inp->fockp_d4);
        qm_input.damp = PyFloat_AsDouble(qm_inp->damp);
        qm_input.vshift = PyFloat_AsDouble(qm_inp->vshift);
        qm_input.kappa = PyFloat_AsDouble(qm_inp->kappa);
        qm_input.pseudo_diag_criteria = PyFloat_AsDouble(qm_inp->pseudo_diag_criteria);
        qm_input.min_heavy_mass = PyFloat_AsDouble(qm_inp->min_heavy_mass);
        qm_input.r_switch_hi = PyFloat_AsDouble(qm_inp->r_switch_hi);
        qm_input.r_switch_lo = PyFloat_AsDouble(qm_inp->r_switch_lo);


        // Error checking on the string input options
        if (!PyString_Check(qm_inp->qmmask)) {
            PyErr_SetString(PyExc_ValueError,
                            "qmmask must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->qmmask) >= 8192) {
            PyErr_SetString(PyExc_ValueError,
                            "qmmask must be smaller than 8192 characters");
            return NULL;
        } else {
            strncpy(qm_input.qmmask, PyString_AsString(qm_inp->qmmask),
                    PyString_Size(qm_inp->qmmask));
        }

        if (!PyString_Check(qm_inp->coremask)) {
            PyErr_SetString(PyExc_ValueError,
                            "coremask must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->coremask) >= 8192) {
            PyErr_SetString(PyExc_ValueError,
                            "coremask must be smaller than 8192 characters");
            return NULL;
        } else {
            strncpy(qm_input.coremask, PyString_AsString(qm_inp->coremask),
                    PyString_Size(qm_inp->coremask));
        }

        if (!PyString_Check(qm_inp->buffermask)) {
            PyErr_SetString(PyExc_ValueError,
                            "buffermask must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->buffermask) >= 8192) {
            PyErr_SetString(PyExc_ValueError,
                            "buffermask must be smaller than 8192 characters");
            return NULL;
        } else {
            strncpy(qm_input.coremask, PyString_AsString(qm_inp->coremask),
                    PyString_Size(qm_inp->coremask));
        }

        if (!PyString_Check(qm_inp->centermask)) {
            PyErr_SetString(PyExc_ValueError,
                            "centermask must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->centermask) >= 8192) {
            PyErr_SetString(PyExc_ValueError,
                            "centermask must be smaller than 8192 characters");
            return NULL;
        } else {
            strncpy(qm_input.coremask, PyString_AsString(qm_inp->coremask),
                    PyString_Size(qm_inp->coremask));
        }

        if (!PyString_Check(qm_inp->dftb_3rd_order)) {
            PyErr_SetString(PyExc_ValueError,
                            "dftb_3rd_order must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->dftb_3rd_order) >= 256) {
            PyErr_SetString(PyExc_ValueError,
                            "coremask must be smaller than 256 characters");
            return NULL;
        } else {
            strncpy(qm_input.coremask, PyString_AsString(qm_inp->coremask),
                    PyString_Size(qm_inp->coremask));
        }

        if (!PyString_Check(qm_inp->qm_theory)) {
            PyErr_SetString(PyExc_ValueError,
                            "qm_theory must be a string");
            return NULL;
        } else if (PyString_Size(qm_inp->qm_theory) >= 12) {
            PyErr_SetString(PyExc_ValueError,
                            "qm_theory must be smaller than 12 characters");
            return NULL;
        } else {
            strncpy(qm_input.coremask, PyString_AsString(qm_inp->coremask),
                    PyString_Size(qm_inp->coremask));
        }

        // Now copy over the arrays. Check that none of them are too large
        if (!PyList_Check(qm_inp->iqmatoms)) {
            PyErr_SetString(PyExc_ValueError,
                            "iqmatoms must be a list of integers");
            return NULL;
        } else if (PyList_Size(qm_inp->iqmatoms) > MAX_QUANTUM_ATOMS) {
            PyErr_SetString(PyExc_ValueError, "iqmatoms is too large");
            return NULL;
        } else {
            Py_ssize_t i;
            for (i = 0; i < PyList_Size(qm_inp->iqmatoms); i++)
                qm_input.iqmatoms[i] = (int) PyInt_AsLong(PyList_GetItem(qm_inp->iqmatoms, i));
            for (i = PyList_Size(qm_inp->iqmatoms); i < MAX_QUANTUM_ATOMS; i++)
                qm_input.iqmatoms[i] = 0;
        }

        if (!PyList_Check(qm_inp->core_iqmatoms)) {
            PyErr_SetString(PyExc_ValueError,
                            "core_iqmatoms must be a list");
            return NULL;
        } else if (PyList_Size(qm_inp->core_iqmatoms) > MAX_QUANTUM_ATOMS) {
            PyErr_SetString(PyExc_ValueError,
                            "core_iqmatoms is too large");
            return NULL;
        } else {
            Py_ssize_t i;
            for (i = 0; i < PyList_Size(qm_inp->core_iqmatoms); i++)
                qm_input.core_iqmatoms[i] = (int) PyInt_AsLong(PyList_GetItem(qm_inp->core_iqmatoms, i));
            for (i = PyList_Size(qm_inp->core_iqmatoms); i < MAX_QUANTUM_ATOMS; i++)
                qm_input.core_iqmatoms[i] = 0;
        }

        if (!PyList_Check(qm_inp->buffer_iqmatoms)) {
            PyErr_SetString(PyExc_ValueError,
                            "buffer_iqmatoms must be a list");
            return NULL;
        } else if (PyList_Size(qm_inp->buffer_iqmatoms) > MAX_QUANTUM_ATOMS) {
            PyErr_SetString(PyExc_ValueError,
                            "buffer_iqmatoms is too large");
            return NULL;
        } else {
            Py_ssize_t i;
            for (i = 0; i < PyList_Size(qm_inp->buffer_iqmatoms); i++)
                qm_input.buffer_iqmatoms[i] = (int) PyInt_AsLong(PyList_GetItem(qm_inp->buffer_iqmatoms, i));
            for (i = PyList_Size(qm_inp->buffer_iqmatoms); i < MAX_QUANTUM_ATOMS; i++)
                qm_input.buffer_iqmatoms[i] = 0;
        }
    }

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
    ret->jfastw = PyInt_FromLong(inp.jfastw);
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
    ret->jfastw = PyInt_FromLong(inp.jfastw);
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
    if (PyType_Ready(&pysander_QmInputOptionsType))
        return;

    // Initialize the module
    m = Py_InitModule3("pysander", pysanderMethods,
                "Python interface into sander energy and force evaluation");

    // Now add the types
    Py_INCREF(&pysander_InputOptionsType);
    PyModule_AddObject(m, "InputOptions", (PyObject*) &pysander_InputOptionsType);
    Py_INCREF(&pysander_EnergyTermsType);
    PyModule_AddObject(m, "EnergyTerms", (PyObject *) &pysander_EnergyTermsType);
    Py_INCREF(&pysander_QmInputOptionsType);
    PyModule_AddObject(m, "QmInputOptions", (PyObject *) &pysander_QmInputOptionsType);
#endif
}

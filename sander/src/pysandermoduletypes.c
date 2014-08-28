/* Define the types that we want to make available. These include the input
 * structs and the energy struct. Make sure these stay up-to-date with the
 * structs defined in the sander API (sander.h), which in turn have to remain
 * up-to-date with the types defined in the Fortran module
 */


// Input options
typedef struct {
    PyObject_HEAD
    PyObject *igb;      // int
    PyObject *alpb;     // int
    PyObject *gbsa;     // int
    PyObject *lj1264;   // int
    PyObject *ipb;      // int
    PyObject *inp;      // int
    PyObject *vdwmeth;  // int
    PyObject *ntb;      // int
    PyObject *ifqnt;    // int

    PyObject *extdiel;  // double
    PyObject *intdiel;  // double
    PyObject *rgbmax;   // double
    PyObject *saltcon;  // double
    PyObject *cut;      // double
    PyObject *dielc;    // double
} pysander_InputOptions;

static void
pysander_InputOptions_dealloc(pysander_InputOptions* self) {
    Py_XDECREF(self->igb);
    Py_XDECREF(self->igb);
    Py_XDECREF(self->alpb);
    Py_XDECREF(self->gbsa);
    Py_XDECREF(self->lj1264);
    Py_XDECREF(self->ipb);
    Py_XDECREF(self->inp);
    Py_XDECREF(self->vdwmeth);
    Py_XDECREF(self->ntb);
    Py_XDECREF(self->ifqnt);

    Py_XDECREF(self->extdiel);
    Py_XDECREF(self->intdiel);
    Py_XDECREF(self->rgbmax);
    Py_XDECREF(self->saltcon);
    Py_XDECREF(self->cut);
    Py_XDECREF(self->dielc);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
pysander_InputOptions_new(PyTypeObject *type) {
    pysander_InputOptions *self;
    self = (pysander_InputOptions *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->igb = PyInt_FromLong(0);
        self->alpb = PyInt_FromLong(0);
        self->gbsa = PyInt_FromLong(0);
        self->lj1264 = PyInt_FromLong(0);
        self->ipb = PyInt_FromLong(0);
        self->inp = PyInt_FromLong(0);
        self->vdwmeth = PyInt_FromLong(0);
        self->ntb = PyInt_FromLong(0);
        self->ifqnt = PyInt_FromLong(0);

        self->extdiel = PyFloat_FromDouble(0.0);
        self->intdiel = PyFloat_FromDouble(0.0);
        self->rgbmax = PyFloat_FromDouble(0.0);
        self->saltcon = PyFloat_FromDouble(0.0);
        self->cut = PyFloat_FromDouble(0.0);
        self->dielc = PyFloat_FromDouble(0.0);
    }

    return (PyObject *) self;
}

static PyMemberDef pysander_InputOptionMembers[] = {
    {"igb", T_OBJECT, offsetof(pysander_InputOptions, igb), 0,
                "GB model to use"},
    {"alpb", T_OBJECT, offsetof(pysander_InputOptions, alpb), 0,
                "Whether to use ALPB"},
    {"gbsa", T_OBJECT, offsetof(pysander_InputOptions, gbsa), 0,
                "Whether to use a SASA term with GB"},
    {"lj1264", T_OBJECT, offsetof(pysander_InputOptions, lj1264), 0,
                "Use the 12-6-4 potential"},
    {"ipb", T_OBJECT, offsetof(pysander_InputOptions, ipb), 0,
                "Use PB"},
    {"inp", T_OBJECT, offsetof(pysander_InputOptions, inp), 0,
                "PB SASA model to use"},
    {"vdwmeth", T_OBJECT, offsetof(pysander_InputOptions, vdwmeth), 0,
                "Whether to use long-range dispersion correction"},
    {"ntb", T_OBJECT, offsetof(pysander_InputOptions, ntb), 0,
                "Whether PBC are present"},
    {"ifqnt", T_OBJECT, offsetof(pysander_InputOptions, ifqnt), 0,
                "Whether to use QM/MM"},

    {"extdiel", T_OBJECT, offsetof(pysander_InputOptions, extdiel), 0,
                "External dielectric constant for GB"},
    {"intdiel", T_OBJECT, offsetof(pysander_InputOptions, intdiel), 0,
                "Internal dielectric constant for GB"},
    {"rgbmax", T_OBJECT, offsetof(pysander_InputOptions, rgbmax), 0,
                "Effective radii cutoff"},
    {"saltcon", T_OBJECT, offsetof(pysander_InputOptions, saltcon), 0,
                "GB salt concentration (M)"},
    {"cut", T_OBJECT, offsetof(pysander_InputOptions, cut), 0,
                "Nonbonded cutoff"},
    {"dielc", T_OBJECT, offsetof(pysander_InputOptions, dielc), 0,
                "dielectric constant"},
    {NULL} /* sentinel */
};

static PyTypeObject pysander_InputOptionsType = {
    PyObject_HEAD_INIT(NULL)
    0,                              // ob_size
    "sander.pysander.InputOptions", // tp_name
    sizeof(pysander_InputOptions),  // tp_basicsize
    0,                              // tp_itemsize
    (destructor)pysander_InputOptions_dealloc, // tp_dealloc
    0,                              // tp_print
    0,                              // tp_getattr
    0,                              // tp_setattr
    0,                              // tp_compare
    0,                              // tp_repr
    0,                              // tp_as_number
    0,                              // tp_as_sequence
    0,                              // tp_as_mapping
    0,                              // tp_hash 
    0,                              // tp_call
    0,                              // tp_str
    0,                              // tp_getattro
    0,                              // tp_setattro
    0,                              // tp_as_buffer
    Py_TPFLAGS_DEFAULT,             // tp_flags
    "List of sander input options", // tp_doc 
    0,		                        // tp_traverse
    0,		                        // tp_clear
    0,		                        // tp_richcompare
    0,		                        // tp_weaklistoffset
    0,		                        // tp_iter
    0,		                        // tp_iternext
    0,                              // tp_methods
    pysander_InputOptionMembers,    // tp_members
    0,                              // tp_getset
    0,                              // tp_base
    0,                              // tp_dict
    0,                              // tp_descr_get
    0,                              // tp_descr_set
    0,                              // tp_dictoffset
    0,                              // tp_init
    0,                              // tp_alloc
    (newfunc)pysander_InputOptions_new,// tp_new
    
};

#if 0
// QM/MM options
typedef struct {
    PyObject_HEAD
    PyObject *iqmatoms; // List, length MAX_QUANTUM_ATOMS
    PyObject *qmgb;
    PyObject *lnk_atomic_no;
    PyObject *ndiis_matrices;
    PyObject *ndiis_attempts;
    PyObject *lnk_method;
    PyObject *qmcharge;
    PyObject *corecharge;
    PyObject *buffercharge;
    PyObject *spin;
    PyObject *qmqmdx;
    PyObject *verbosity;
    PyObject *printcharges;
    PyObject *printdipole;
    PyObject *print_eigenvalues;
    PyObject *peptide_corr;
    PyObject *itrmax;
    PyObject *printbondorders;
    PyObject *qmshake;
    PyObject *qmmmrij_incore;
    PyObject *qmqm_erep_incore;
    PyObject *pseudo_diag;
    PyObject *qm_ewald;
    PyObject *qm_pme;
    PyObject *kmaxqx;
    PyObject *kmaxqy;
    PyObject *kmaxqz;
    PyObject *ksqmaxq;
    PyObject *kappa;
    PyObject *qmmm_int;
    PyObject *adjust_q;
    PyObject *diag_routine;
    PyObject *density_predict;
    PyObject *fock_predict;
    PyObject *vsolv;
    PyObject *dftb_maxiter;
    PyObject *dftb_disper;
    PyObject *dftb_chg;
    PyObject *abfqmmm;
    PyObject *hot_spot;
    PyObject *qmmm_switch;
    PyObject *core_iqmatoms; // List, MAX_QUANTUM_ATOMS
    PyObject *buffer_iqmatoms; // List, MAX_QUANTUM_ATOMS
    // Floats (input parameters)
    PyObject *qmcut;
    PyObject *lnk_dis;
    PyObject *scfconv;
    PyObject *errconv;
    PyObject *dftb_telec;
    PyObject *dftb_telec_step;
    PyObject *fockp_d1;
    PyObject *fockp_d2;
    PyObject *fockp_d3;
    PyObject *fockp_d4;
    PyObject *damp;
    PyObject *vshift;
    PyObject *pseudo_diag_criteria;
    PyObject *min_heavy_mass;
    PyObject *r_switch_hi;
    PyObject *r_switch_lo;
    // Strings
    PyObject *qmmask;         // length 8192
    PyObject *coremask;       // length 8192
    PyObject *buffermask;     // length 8192
    PyObject *centermask;     // length 8192
    PyObject *dftb_3rd_order; // length 256
    PyObject *qm_theory;      // length 12
} pysander_QmInputOptions;

static PyObject *
pysander_QmInputOptions_new(PyTypeObject *type) {
    pysander_QmInputOptions *self;
    self = (pysander_QmInputOptions *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->igb = PyInt_FromLong(0);
        self->alpb = PyInt_FromLong(0);
        self->gbsa = PyInt_FromLong(0);
        self->lj1264 = PyInt_FromLong(0);
        self->ipb = PyInt_FromLong(0);
        self->inp = PyInt_FromLong(0);
        self->vdwmeth = PyInt_FromLong(0);
        self->ntb = PyInt_FromLong(0);
        self->ifqnt = PyInt_FromLong(0);

        self->extdiel = PyFloat_FromDouble(0.0);
        self->intdiel = PyFloat_FromDouble(0.0);
        self->rgbmax = PyFloat_FromDouble(0.0);
        self->saltcon = PyFloat_FromDouble(0.0);
        self->cut = PyFloat_FromDouble(0.0);
        self->dielc = PyFloat_FromDouble(0.0);
    }

    return (PyObject *) self;
}
#endif /* 0 */

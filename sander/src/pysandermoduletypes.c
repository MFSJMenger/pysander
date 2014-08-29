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
    Py_DECREF(self->igb);
    Py_DECREF(self->igb);
    Py_DECREF(self->alpb);
    Py_DECREF(self->gbsa);
    Py_DECREF(self->lj1264);
    Py_DECREF(self->ipb);
    Py_DECREF(self->inp);
    Py_DECREF(self->vdwmeth);
    Py_DECREF(self->ntb);
    Py_DECREF(self->ifqnt);

    Py_DECREF(self->extdiel);
    Py_DECREF(self->intdiel);
    Py_DECREF(self->rgbmax);
    Py_DECREF(self->saltcon);
    Py_DECREF(self->cut);
    Py_DECREF(self->dielc);
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

//#if 0
// Energy struct
typedef struct {
    PyObject_HEAD
    PyObject *tot;
    PyObject *vdw;
    PyObject *elec;
    PyObject *gb;
    PyObject *bond;
    PyObject *angle;
    PyObject *dihedral;
    PyObject *vdw_14;
    PyObject *elec_14;
    PyObject *constraint;
    PyObject *polar;
    PyObject *hbond;
    PyObject *surf;
    PyObject *scf;
    PyObject *disp;
    PyObject *dvdl;
    PyObject *angle_ub;
    PyObject *imp;
    PyObject *cmap;
    PyObject *emap;
    PyObject *les;
    PyObject *noe;
    PyObject *pb;
    PyObject *rism;
    PyObject *ct;
    PyObject *amd_boost;
} pysander_EnergyTerms;

static PyObject *
pysander_EnergyTerms_new(PyTypeObject *type) {
    pysander_EnergyTerms *self;
    self = (pysander_EnergyTerms *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->tot = PyFloat_FromDouble(0.0);
        self->vdw = PyFloat_FromDouble(0.0);
        self->elec = PyFloat_FromDouble(0.0);
        self->gb = PyFloat_FromDouble(0.0);
        self->bond = PyFloat_FromDouble(0.0);
        self->angle = PyFloat_FromDouble(0.0);
        self->dihedral = PyFloat_FromDouble(0.0);
        self->vdw_14 = PyFloat_FromDouble(0.0);
        self->elec_14 = PyFloat_FromDouble(0.0);
        self->constraint = PyFloat_FromDouble(0.0);
        self->polar = PyFloat_FromDouble(0.0);
        self->hbond = PyFloat_FromDouble(0.0);
        self->surf = PyFloat_FromDouble(0.0);
        self->scf = PyFloat_FromDouble(0.0);
        self->disp = PyFloat_FromDouble(0.0);
        self->dvdl = PyFloat_FromDouble(0.0);
        self->angle_ub = PyFloat_FromDouble(0.0);
        self->imp = PyFloat_FromDouble(0.0);
        self->cmap = PyFloat_FromDouble(0.0);
        self->emap = PyFloat_FromDouble(0.0);
        self->les = PyFloat_FromDouble(0.0);
        self->noe = PyFloat_FromDouble(0.0);
        self->pb = PyFloat_FromDouble(0.0);
        self->rism = PyFloat_FromDouble(0.0);
        self->ct = PyFloat_FromDouble(0.0);
        self->amd_boost = PyFloat_FromDouble(0.0);
    }

    return (PyObject *) self;
}

static void
pysander_EnergyTerms_dealloc(pysander_EnergyTerms* self) {
    Py_DECREF(self->tot);
    Py_DECREF(self->vdw);
    Py_DECREF(self->elec);
    Py_DECREF(self->gb);
    Py_DECREF(self->bond);
    Py_DECREF(self->angle);
    Py_DECREF(self->dihedral);
    Py_DECREF(self->vdw_14);
    Py_DECREF(self->elec_14);
    Py_DECREF(self->constraint);
    Py_DECREF(self->polar);
    Py_DECREF(self->hbond);
    Py_DECREF(self->surf);
    Py_DECREF(self->scf);
    Py_DECREF(self->disp);
    Py_DECREF(self->dvdl);
    Py_DECREF(self->angle_ub);
    Py_DECREF(self->imp);
    Py_DECREF(self->cmap);
    Py_DECREF(self->emap);
    Py_DECREF(self->les);
    Py_DECREF(self->noe);
    Py_DECREF(self->pb);
    Py_DECREF(self->rism);
    Py_DECREF(self->ct);
    Py_DECREF(self->amd_boost);
    self->ob_type->tp_free((PyObject*)self);
}

static PyMemberDef pysander_EnergyTermsMembers[] = {
    {"tot", T_OBJECT, offsetof(pysander_EnergyTerms, tot), 0,
                "Total potential energy"},
    {"vdw", T_OBJECT, offsetof(pysander_EnergyTerms, vdw), 0,
                "van der Waals energy (excluding 1-4)"},
    {"elec", T_OBJECT, offsetof(pysander_EnergyTerms, elec), 0,
                "Electrostatic energy (excluding 1-4)"},
    {"gb", T_OBJECT, offsetof(pysander_EnergyTerms, gb), 0,
                "Generalized Born polar solvation energy"},
    {"bond", T_OBJECT, offsetof(pysander_EnergyTerms, bond), 0,
                "Bond energy"},
    {"angle", T_OBJECT, offsetof(pysander_EnergyTerms, angle), 0,
                "Angle energy"},
    {"dihedral", T_OBJECT, offsetof(pysander_EnergyTerms, dihedral), 0,
                "Dihedral energy (including impropers)"},
    {"vdw_14", T_OBJECT, offsetof(pysander_EnergyTerms, vdw_14), 0,
                "1-4 van der Waals energy"},
    {"elec_14", T_OBJECT, offsetof(pysander_EnergyTerms, elec_14), 0,
                "1-4 electrostatic energy"},
    {"constraint", T_OBJECT, offsetof(pysander_EnergyTerms, constraint), 0,
                "Restraint energy"},
    {"polar", T_OBJECT, offsetof(pysander_EnergyTerms, polar), 0,
                "Polarization energy (for polarized force fields)"},
    {"hbond", T_OBJECT, offsetof(pysander_EnergyTerms, hbond), 0,
                "Hydrogen bond (10-12 potential) energy"},
    {"surf", T_OBJECT, offsetof(pysander_EnergyTerms, surf), 0,
                "Nonpolar solvation energy for implicit solvent"},
    {"scf", T_OBJECT, offsetof(pysander_EnergyTerms, scf), 0,
                "QM energy"},
    {"disp", T_OBJECT, offsetof(pysander_EnergyTerms, disp), 0,
                "Dispersion nonpolar solvation energy from PB"},
    {"dvdl", T_OBJECT, offsetof(pysander_EnergyTerms, dvdl), 0,
                "DV/DL from TI"},
    {"angle_ub", T_OBJECT, offsetof(pysander_EnergyTerms, angle_ub), 0,
                "Urey-Bradley energy (CHARMM FF only)"},
    {"imp", T_OBJECT, offsetof(pysander_EnergyTerms, imp), 0,
                "Improper torsion energy (CHARMM FF only)"},
    {"cmap", T_OBJECT, offsetof(pysander_EnergyTerms, cmap), 0,
                "Coupled torsion correction map energy (CHARMM only)"},
    {"emap", T_OBJECT, offsetof(pysander_EnergyTerms, emap), 0,
                "Energy map restraint energy"},
    {"les", T_OBJECT, offsetof(pysander_EnergyTerms, les), 0,
                "LES energy"},
    {"noe", T_OBJECT, offsetof(pysander_EnergyTerms, noe), 0,
                "NOE restraint energy"},
    {"pb", T_OBJECT, offsetof(pysander_EnergyTerms, pb), 0,
                "PB polar solvation energy"},
    {"rism", T_OBJECT, offsetof(pysander_EnergyTerms, rism), 0,
                "3D-RISM energy"},
    {"ct", T_OBJECT, offsetof(pysander_EnergyTerms, ct), 0,
                "????"},
    {"amd_boost", T_OBJECT, offsetof(pysander_EnergyTerms, amd_boost), 0,
                "accelerated MD boost energy"},
    {NULL} /* sentinel */
};

static PyTypeObject pysander_EnergyTermsType = {
    PyObject_HEAD_INIT(NULL)
    0,                              // ob_size
    "sander.pysander.EnergyTerms",  // tp_name
    sizeof(pysander_EnergyTerms),   // tp_basicsize
    0,                              // tp_itemsize
    (destructor)pysander_EnergyTerms_dealloc, // tp_dealloc
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
    "List of sander energy terms",  // tp_doc 
    0,		                        // tp_traverse
    0,		                        // tp_clear
    0,		                        // tp_richcompare
    0,		                        // tp_weaklistoffset
    0,		                        // tp_iter
    0,		                        // tp_iternext
    0,                              // tp_methods
    pysander_EnergyTermsMembers,    // tp_members
    0,                              // tp_getset
    0,                              // tp_base
    0,                              // tp_dict
    0,                              // tp_descr_get
    0,                              // tp_descr_set
    0,                              // tp_dictoffset
    0,                              // tp_init
    0,                              // tp_alloc
    (newfunc)pysander_EnergyTerms_new,// tp_new
    
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

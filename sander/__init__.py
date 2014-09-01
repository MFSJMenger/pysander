import sander.pysander as _pys

# Add some of the pysander members directly to the sander namespace
InputOptions = _pys.InputOptions
QmInputOptions = _pys.QmInputOptions
setup = _pys.setup
cleanup = _pys.cleanup
pme_input = _pys.pme_input
gas_input = _pys.gas_input

def qm_input():
    """
    Returns a populated set of QM input options. Only here for consistency with
    gas_input and pme_input -- QmInputOptions can be instantiated directly
    """
    return QmInputOptions()

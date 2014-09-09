try:
    import numpy as _np
except ImportError:
    _np = None

__all__ = ['InputOptions', 'QmInputOptions', 'setup', 'cleanup', 'pme_input',
           'gas_input', 'natom', 'energy_forces', 'set_positions', 'set_box']

from array import array as _array
import pysander as _pys

# Add some of the pysander members directly to the sander namespace
InputOptions = _pys.InputOptions
QmInputOptions = _pys.QmInputOptions
setup = _pys.setup
cleanup = _pys.cleanup
pme_input = _pys.pme_input
gas_input = _pys.gas_input
natom = _pys.natom
energy_forces = _pys.energy_forces
set_box = _pys.set_box

def qm_input():
    """
    Returns a populated set of QM input options. Only here for consistency with
    gas_input and pme_input -- QmInputOptions can be instantiated directly
    """
    return QmInputOptions()

def set_positions(positions):
    """
    Sets the particle positions of the active system from the passed list of
    positions. Supports both lists, numpy.ndarray and numpy.ndarray objects
    """
    if isinstance(positions, _np.ndarray) or isinstance(positions, _array):
        return _pys.set_positions(positions.tolist())
    return _pys.set_positions(positions)

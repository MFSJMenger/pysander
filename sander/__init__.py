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
cleanup = _pys.cleanup
pme_input = _pys.pme_input
gas_input = _pys.gas_input
natom = _pys.natom
energy_forces = _pys.energy_forces
set_box = _pys.set_box

def setup(prmtop, coordinates, box, mm_options, qm_options=None):
    """Sets up a sander calculation

    Parameters
    ----------
    prmtop : str
        Name of the prmtop file to use to set up the calculation
    coordinates : list/iterable
        list of coordinates
    box : list/iterable or None
        list of 3 box lengths and 3 box angles. Can be None if no box is
        required
    mm_options : InputOptions
        struct with sander options
    qm_options : QmInputOptions (optional)
        struct with the QM options in sander QM/MM calculations
    """
    # Convert from numpy arrays to regular arrays
    if hasattr(coordinates, 'tolist'): # works for numpy.ndarray and array.array
        coordinates = coordinates.tolist()
    if hasattr(box, 'tolist'):
        box = box.tolist()
    if not box:
        box = [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]
    try:
        box = [float(x) for x in box]
    except TypeError:
        raise TypeError('box must be an iterable with 6 numerical elements')
    if len(box) != 6:
        raise ValueError('box must have 6 elements')
    if qm_options is None:
        return _pys.setup(prmtop, coordinates, box, mm_options)
    return _pys.setup(prmtop, coordinates, box, mm_options, qm_options)

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
    if hasattr(positions, 'tolist'): # works for array.array and numpy.ndarray
        _pys.set_positions(positions.tolist())
    return _pys.set_positions(positions)

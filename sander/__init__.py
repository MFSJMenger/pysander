from chemistry.amber.readparm import AmberParm, Rst7
import tempfile
try:
    import numpy as _np
except ImportError:
    _np = None

__all__ = ['InputOptions', 'QmInputOptions', 'setup', 'cleanup', 'pme_input',
           'gas_input', 'natom', 'energy_forces', 'set_positions', 'set_box',
           'is_setup']

from array import array as _array
try:
    import pysander as _pys
except ImportError:
    raise ImportError('Could not import the compiled Python-sander interface. '
                      'Make sure you have the Python development libraries '
                      'installed and try rebuilding the serial installation '
                      'of AMBER.')

# Add some of the pysander members directly to the sander namespace
InputOptions = _pys.InputOptions
QmInputOptions = _pys.QmInputOptions
cleanup = _pys.cleanup
pme_input = _pys.pme_input
gas_input = _pys.gas_input
natom = _pys.natom
energy_forces = _pys.energy_forces
set_box = _pys.set_box
is_setup = _pys.is_setup

# For Python3 compatibility
try:
    basestring
except NameError:
    basestring = str

# Ideally we'd use contextlib.contextmanager and turn the function into a
# context manager directly as a generator. However, contextlib was added in
# Python 2.5, and we desire to keep Python 2.4 support while still allowing the
# use of the context manager. As a result, we turn setup into a class (yuck)
# with __enter__ and __exit__ methods that implement the context manager for
# Python 2.5+, or do nothing in Python 2.4. It behaves the same way that the
# function would.

class setup(object):
    """ Sets up a sander calculation. This supports acting like a context
    manager such that the cleanup routine is called upon exiting the context. It
    can also be called as a standalone function.

    Parameters
    ----------
    prmtop : AmberParm or str
        Name of the prmtop file to use to set up the calculation or an AmberParm
        instance
    coordinates : list/iterable or str
        list of coordinates or name of the inpcrd file
    box : list/iterable or None
        list of 3 box lengths and 3 box angles. Can be None if no box is
        required or if the box will be read in from the coordinates
    mm_options : InputOptions
        struct with sander options
    qm_options : QmInputOptions (optional)
        struct with the QM options in sander QM/MM calculations

    Examples
    --------

    The following are equivalent invocations which each make sure that the
    sander data structures are cleaned up afterwards

    >>> with sander.setup("prmtop", inpcrd.coords, inpcrd.box, mm_options):
    ...     e, f = sander.energy_forces()
    ... 
    >>> sander.is_setup()
    False

    Without a context manager (e.g., Python 2.4 and earlier), which ensures that
    cleanup is done

    >>> try:
    ...     sander.setup("prmtop", inpcrd.coords, inpcrd.box, mm_options)
    ...     e, f = sander.energy_forces()
    ... finally:
    ...     if sander.is_setup():
    ...         sander.cleanup()
    ... 
    >>> sander.is_setup()
    False

    If you want the sander system to stay set up when the current function ends
    and persist until another function call, simply do not execute a cleanup in
    a `finally` clause and do not use a context manager

    >>> sander.setup("prmtop", inpcrd.coords, inpcrd.box, mm_options)
    >>> e, f = sander.energy_forces()
    >>> sander.is_setup()
    True
    """

    def __init__(self, prmtop, coordinates, box, mm_options, qm_options=None):
        # Handle the case where the coordinates are actually a restart file
        if isinstance(coordinates, basestring):
            # This is a restart file name. Parse it and make sure the coordinates
            # and box
            rst = Rst7.open(coordinates)
            try:
                coordinates = rst.coordinates.tolist()
            except AttributeError:
                coordinates = rst.coordinates
            if rst.hasbox and not box:
                try:
                    box = rst.box.tolist()
                except AttributeError:
                    box = rst.box

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

        # Check if the prmtop is an AmberParm instance or not. If it is, write out a
        # temporary prmtop file
        if isinstance(prmtop, AmberParm):
            parm = tempfile.mktemp(suffix='.parm7')
            prmtop.writeParm(parm)
        elif not isinstance(prmtop, basestring):
            raise TypeError('prmtop must be an AmberParm or string')
        else:
            parm = prmtop

        # Error checking
        if mm_options.ifqnt != 0 and qm_options is None:
            raise ValueError("qm_options must be provided if QM/MM is requested")

        # Call the setup routine
        if qm_options is None:
            _pys.setup(parm, coordinates, box, mm_options)
        else:
            _pys.setup(parm, coordinates, box, mm_options, qm_options)

    def __enter__(self):
        """ Nothing needs to be done here """
        pass

    def __exit__(self, *args, **kwargs):
        """ Make sure that sander is cleaned up """
        if _pys.is_setup(): _pys.cleanup()

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
        return _pys.set_positions(positions.tolist())
    return _pys.set_positions(positions)

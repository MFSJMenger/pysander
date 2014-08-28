
from distutils.core import setup, Extension
import os

amberhome = os.getenv('AMBERHOME')

if amberhome is None:
    raise RuntimeError('AMBERHOME is not set! Cannot compile pysander')

packages = ['sander']

pysander = Extension('sander.pysander',
                     sources=['sander/src/pysandermodule.c'],
                     include_dirs=[os.path.join(amberhome, 'include')],
                     library_dirs=[os.path.join(amberhome, 'lib')],
                     libraries=['sander'])

setup(name='sander', ext_modules=[pysander], packages=packages)

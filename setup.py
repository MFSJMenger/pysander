
from distutils.core import setup, Extension
import os
import shutil
import sys

amberhome = os.getenv('AMBERHOME')
assert amberhome is not None

if amberhome is None:
    raise RuntimeError('AMBERHOME is not set! Cannot compile pysander')

packages = ['sander', 'sanderles']

os.system('/bin/rm -fr sanderles')
shutil.copytree('sander', 'sanderles')
incdir = [os.path.join(amberhome, 'include'),
          os.path.join(amberhome, 'AmberTools', 'src', 'include')]
libdir = [os.path.join(amberhome, 'lib')]

try:
    pysander = Extension('sander.pysander',
                         sources=['sander/src/pysandermodule.c'],
                         include_dirs=incdir, library_dirs=libdir,
                         libraries=['sander'])
    pysanderles = Extension('sanderles.pysander',
                            sources=['sanderles/src/pysandermodule.c'],
                            include_dirs=incdir, library_dirs=libdir,
                            libraries=['sanderles'],
                            define_macros=[('LES', None)])
    setup(name='sander',
          version="15.0",
          license='GPL v2 or later',
          author='Jason Swails',
          author_email='jason.swails -at- gmail.com',
          description='SANDER energy/force evaluation',
          ext_modules=[pysander, pysanderles],
          packages=packages,
    )
finally:
    os.system('/bin/rm -fr sanderles')

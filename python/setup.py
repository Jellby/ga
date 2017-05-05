import ConfigParser
import os
import sys

from distutils.core import setup
from distutils.extension import Extension
from distutils.sysconfig import get_config_vars

# numpy is required -- attempt import
try:
    import numpy
except ImportError:
    print "numpy is required"
    raise

# cython is optional -- attempt import
use_cython = False
try:
    from Cython.Build import cythonize
    use_cython = True
except:
    pass

# read site.cfg for preprocessor/linker flags
config = ConfigParser.RawConfigParser()
config.read('site.cfg')

ga_cc = config.get('ga-config', 'cc')
ga_cppflags = config.get('ga-config', 'cppflags')
ga_ldflags = config.get('ga-config', 'ldflags')
ga_clibs = config.get('ga-config', 'clibs')

if 'CC' not in os.environ:
    os.environ['CC'] = ga_cc
if 'LDSHARED' not in os.environ:
    # take a lucky guess and reuse the same flags Python used
    flags = get_config_vars('LDSHARED')[0].strip().split()
    assert(flags)
    flags[0] = ga_cc
    os.environ['LDSHARED'] = ' '.join(flags)
if 'ARCHFLAGS' not in os.environ:
    os.environ['ARCHFLAGS'] = ''

linalg_include = []
linalg_library = []
linalg_lib = []
if 'Accelerate' in ga_clibs or 'vecLib' in ga_clibs:
    path = "/System/Library/Frameworks/Accelerate.framework/Frameworks/vecLib.framework/Versions/A"
    linalg_include = []
    if os.path.exists(path):
        linalg_library = [path]
        linalg_lib = ["LAPACK","BLAS"]
    # remove '-framework Accelerate' from flags
    ga_clibs = ga_clibs.replace('-framework','')
    ga_clibs = ga_clibs.replace('Accelerate','')
    ga_clibs = ga_clibs.replace('vecLib','')

include_dirs = [numpy.get_include()]
library_dirs = []
libraries = []

# add the GA stuff
for dir in ga_cppflags.split():
    dir = dir.strip()
    include_dirs.append(dir.replace('-I',''))
for dir in ga_ldflags.split():
    dir = dir.strip()
    library_dirs.append(dir.replace('-L',''))
for part in ga_clibs.split():
    part = part. strip()
    if '-L' in part:
        library_dirs.append(part.replace('-L',''))
    elif '-l' in part:
        libraries.append(part.replace('-l',''))

if linalg_include:
    include_dirs.extend(linalg_include)
if linalg_library:
    library_dirs.extend(linalg_library)
if linalg_lib:
    libraries.extend(linalg_lib)

sources = ["ga.c"]
if use_cython:
    sources = ["ga.pyx"]

include_dirs.append('.')

ext_modules = [
    Extension(
        name="ga",
        sources=sources,
        include_dirs=include_dirs,
        library_dirs=library_dirs,
        libraries=libraries
    )
]

if use_cython:
    ext_modules = cythonize(ext_modules)

setup(
        name = "Global Arrays",
        ext_modules = ext_modules
)

"""IO Rodeo Potentiostat

"""
from setuptools import setup, find_packages
from codecs import open
from os import path

here = path.abspath(path.dirname(__file__))

with open(path.join(here, 'README.rst'), encoding='utf-8') as f: 
    long_description = f.read()

setup(
    name='potentiostat',
    version='0.0.1dev1',
    description='Serial interface to IO Rodeo Potentiostat',
    long_description=long_description,
    url='https://bitbucket.org/iorodeo/potentiostat',
    author='Will Dickson',
    author_email='will@iorodeo.com',
    license='MIT',

    classifiers=[
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'Intended Audience :: Science/Research',
        'Topic :: Scientific/Engineering :: Chemistry',
        'Topic :: Software Development :: Libraries',
        'Topic :: Software Development :: Libraries :: Python Modules',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 2.7',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.3',
        'Programming Language :: Python :: 3.4',
        'Programming Language :: Python :: 3.5',
        'Operating System :: POSIX', 
        'Operating System :: Microsoft :: Windows', 
        'Operating System :: MacOS :: MacOS X',
    ],

    keywords='Serial interface for IO Rodeo Potentiostat',
    packages=find_packages(exclude=['docs', 'tests']),

    install_requires=['pyserial','progressbar33'],
)

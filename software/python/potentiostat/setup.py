"""
iorodeo-potentiostat
---------------------

Python interface to IO Rodeo's Potentiostat Shield for the teensy 3.2 development 
board.

Example
--------

.. code:: python

    from potentiostat import Potentiostat

    dev = Potentiostat('/dev/ttyACM0')
    dev.set_curr_range('100uA')
    dev.set_sample_period(10)
    
    name = 'cyclic'
    param = {
            'quietValue' : 0.0,
            'quietTime'  : 1000,
            'amplitude'  : 2.0,
            'offset'     : 0.0,
            'period'     : 1000,
            'numCycles'  : 5,
            'shift'      : 0.0,
            }
    
    dev.set_param(name,param)
    t,volt,curr = dev.run_test(name,display='pbar')


Install
--------

.. code:: bash

    $ pip install iorodeo-potentiostat


Links
-----

* Documentation http://stuff.iorodeo.com/docs/potentiostat
* Download https://bitbucket.org/iorodeo/potentiostat

"""
from setuptools import setup, find_packages
from os import path

here = path.abspath(path.dirname(__file__))

setup(
    name='iorodeo-potentiostat',
    version='0.0.3',
    description='Serial interface to IO Rodeo Potentiostat',
    long_description=__doc__,
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
    packages=find_packages(exclude=['docs', 'tests', 'examples']),

    install_requires=['pyserial','progressbar33'],
)

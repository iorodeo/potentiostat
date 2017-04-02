###############
Getting Started
###############

This section provides a short guide to help you begin using the 
**iorodeo-potentiostat** library.

This module is tested on Python 2.7 and Python 3.x. 

************
Installation
************

If you are developing with the library it is very likely that you will want to
use `virtualenv`_ during installation. A tutorial describing how to use virtualenv
can be found here `virtualenv tutorial`_  and more detialed information can be
found in the `virtualenv documentation`_.  If you are using the library on
Windows you might want to look this additional tutorial `Python, pip and
virtuanenv on Windows`_. 

Once you have created and activated a virtual environment the library can be
installed using pip as follows:

.. code-block:: bash

  $ pip install iorodeo-potentiostat


If you are installing using pip then all required dependencies should
automatically be downloaded and installed when running this command.

An alternative installation method is to download and install from source. If
you would like to install in this manner the  source for the library can be
found in the `potentiostat shield repository`_.  To install the software would
run the following command from within the module's top level directory (software/python/potentiostat).


.. code-block:: bash

  $ python setup.py install

 
If your are installing from source (not with pip) then you will also need to
install the following dependencies:

* `Pyserial >= 2.6`_ 
* `Progressbar33`_ 


Driver (Windows Only)
=====================

On versions of windows < 10. You will need to install a driver in order to communicate with the
teensy 3.2 as a serial port. The easiest way to do this is to run the `teensyduino installer`_.

Note, this step is not required on Linux or on Mac OS.


udev rules (Linux only)
=======================
On Linux you may want to give non-root users permission to use the teensy
device. This can be done by adding the `49-teensy.rules`_ file to the
/etc/udev/rules.d directory and reloading the rules using udevadm to reload the
rules for udev.

Copy to /etc/udev/rules.d as follows

.. code-block:: bash

  $ sudo cp 49-teensy.rules /etc/udev/rules.d/

Reload udev rules

.. code-block:: bash

  $ sudo udevadm control --reload-rules


************************
Creating a device object
************************

The first step to using the Potentiostat via the library is to create a device
object. In order to do this you will need to know the name of **port** on the
computer which is associated with the potentiostat shield. The name of this
port will vary depending on your computer, OS, etc. On linux this port will be
named something like /dev/ttyACM0, /dev/ttyACM1, etc. On Windows it will be
named something like COM1, COM2, etc. 

A device object can be created as follows

.. code-block:: python 

  from potentiostat import Potentiostat

  dev = Potentiostat('/dev/ttyACM0')



**********************************
Getting list of voltametric tests
**********************************

A list of all of the voltammetric tests supported by the current firmware on
the Potentiostat Shield's teensy 3.2 can be obtained using the
:meth:`~potentiostat.Potentiostat.get_test_names` method.

.. code-block:: python

  from potentiostat import Potentiostat

  dev = Potentiostat('/dev/ttyACM0')
  test_names = dev.get_test_names()

This method will return a list such as that given below

.. code-block:: python

  ['cyclic', 'sinusoid', 'constant', 'linearSweep', 'chronoamp', 'multiStep']
  

************************************
Getting voltammetric test parameters
************************************

The current parameter values used for a particular voltammetric test, stored
in teensy 3.2 on the potentiostat shield, can be retrieved from the device using the
:meth:`~potentiostat.Potentiostat.get_param` method. 

The following example shows how to get the current parameter values for the *linearSweep* test.

.. code-block:: python

  from potentiostat import Potentiostat

  dev = Potentiostat('/dev/ttyACM0')
  param = dev.get_param('linearSweep')

This method returns a dictionay containing the current parameters for the
specified test, for *linearSweep* example above be might get

.. code-block:: python

  {'quietTime': 0, 'quietValue': 0.0, 'finalValue': 0.5, 'startValue': -0.5, 'duration': 2000}

  

************************************
Setting voltammetric test parameters
************************************

*********************************
Setting measurement current range
*********************************

*******************
Setting sample rate
*******************

****************************
Running a voltammetric tests
****************************

****************************
Setting output voltage range
****************************

****************
Manual operation
****************

************************************
Setting device identification number
************************************

**********
References
**********

.. target-notes::

.. _`virtualenv`: https://pypi.python.org/pypi/virtualenv
.. _`virtualenv tutorial`: http://python-guide-pt-br.readthedocs.io/en/latest/dev/virtualenvs/ 
.. _`virtualenv documentation`: https://virtualenv.pypa.io/en/stable/ 
.. _`potentiostat shield repository`: https://bitbucket.org/iorodeo/potentiostat/
.. _`Python, pip and virtuanenv on Windows`: http://www.tylerbutler.com/2012/05/how-to-install-python-pip-and-virtualenv-on-windows-with-powershell/
.. _`Pyserial >= 2.6`: https://pythonhosted.org/pyserial/
.. _`Progressbar33`: https://pypi.python.org/pypi/progressbar33 
.. _`teensyduino installer`: https://www.pjrc.com/teensy/td_download.html
.. _`49-teensy.rules`: https://www.pjrc.com/teensy/49-teensy.rules

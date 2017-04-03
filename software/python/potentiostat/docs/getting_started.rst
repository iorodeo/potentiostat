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
can be found here `virtualenv tutorial`_  and more detailed information can be
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

  pstat = Potentiostat('/dev/ttyACM0')


This will open a connection to the device. 

Note, in order to avoid too much repetition,  in all of the examples which
follow we will assume that created a Potentiostat device object named pstat.



**********************************
Getting list of voltametric tests
**********************************

A list of all of the voltammetric tests supported by the current firmware on
the Potentiostat Shield's teensy 3.2 can be obtained using the
:meth:`~potentiostat.Potentiostat.get_test_names` method.

.. code-block:: python

  test_names = pstat.get_test_names()

This method will return a list such as that given below

.. code-block:: python

  test_names = ['cyclic', 'sinusoid', 'constant', 'linearSweep', 'chronoamp', 'multiStep']
  

************************************
Getting voltammetric test parameters
************************************

The current parameter values used for a particular voltammetric test, which are stored
in teensy 3.2 on the potentiostat shield, can be retrieved from the device using the
:meth:`~potentiostat.Potentiostat.get_param` method. 

The following example shows how to get the current parameter values for the *linearSweep* test.

.. code-block:: python

  param = pstat.get_param('linearSweep')

This method returns a dictionay containing the current set of parameters for the
specified test. For example, for the *linearSweep* example above be result would be something
like this  

.. code-block:: python

  param = {'quietTime': 0, 'quietValue': 0.0, 'finalValue': 0.5, 'startValue': -0.5, 'duration': 2000}


Note, all time values, such as quietTime and duration, are given in (ms). All
output voltages, such as quietValue, startValue and finalValue, are given in
(V).  A complete description of the parameters for all voltammetric tests is
given in the :ref:`test_param_ref` section of the documentation.


************************************
Setting voltammetric test parameters
************************************

The :meth:`~potentiostat.Potentiostat.set_param` method can be used to set the
parameters used for a specific voltammetric test. The parameters are stored in
RAM (voltile memory) on teensy 3.2 . They will retain their value, for the
specified test,  as long as the teensy 3.2 has power or until changed via
another call to the set_param method. 

The following examples demonstrates how to set the parameters for the *linearSweep* test.

.. code-block:: python

  param = {'quietTime': 0, 'quietValue': 0.0, 'finalValue': 0.5, 'startValue': -0.5, 'duration': 2000}

  pstat.set_param('linearSweep',param)
  
Note, all time values, such as quietTime and duration, are given in (ms). All
output voltages, such as quietValue, startValue and finalValue, are given in
(V).  A complete description of the parameters for all voltammetric tests is
given in the :ref:`test_param_ref` section of the documentation.

*****************************************
Getting/setting measurement current range
*****************************************

The potentiostat shield has four programmable current measurement ranges. The
exact values for the avialable ranges is determined by the hardware variant of
the device you are using. The library will automatically detect the hardvariant of
the device for you.  You can retrieve  the current ranges available
on your device using the :meth:`~potentiostat.Potentiostat.get_all_curr_range` method.
For example, 

.. code-block:: python

  curr_range_list = pstat.get_all_curr_range()


This will return a list of current range strings such as that given below

.. code-block:: python

  curr_range_list = ['1uA', '10uA', '100uA', '1000uA']


You can get the current measurement range which your device is currently using 
the :meth:`~potentiostat.Potentiostat.get_curr_range` method. For example, 

.. code-block:: python

  curr_range = pstat.get_curr_range()

This will return a string representation of the current measurement range -  something like this

.. code-block:: python

  curr_range = '10uA'


In order to set the desired current measurement range on your device you can
use the :meth:`~potentiostat.Potentiostat.set_curr_range` method. For example,
to change the current range to '100uA' you could to the following

.. code-block:: python

  pstat.set_curr_range('100uA')


***************************
Getting/setting sample rate
***************************
When running a test the device returns measurements at a specified rate
(samples/sec) for the duration of the test.  You can use the
:meth:`~potentiostat.Potentiostat.get_sample_rate` to retrieve the current sample
rate used for measurements. For example,  

.. code-block:: python

  sample_rate = pstat.get_sample_rate()

This method will return the current sample rate, in samples/sec, as float.

If you want to change the sample rate used for measurements you can use the
:meth:`~potentiostat.Potentiostat.set_sample_rate` method. For example, to set the
current sample rate to 50 samples/sec

.. code-block:: python

  pstat.set_sample_rate(50.0)


As an alternative, there also exist methods for specifying the sample period,
i.e., the time dt (sec) between samples or 1.0/(sample rate).  While these
methods are somewhat redundant in that the ultimately do the same thing as the
set/get sample rate methods they are provided for convienence.

The :meth:`~potentiostat.Potentiostat.get_sample_period` method returns the sample_period in seconds.

.. code-block:: python

   sample_period = pstat.get_sample_period()


The :meth:`~potentiostat.Potentiostat.set_sample_period` method sets the sample period (given in seconds). 

.. code-block:: python

   pstat.set_sample_period(0.02)


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

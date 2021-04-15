############
Installation
############

This library is tested on Python 2.7 and Python 3.x. 

********************
Installing from PyPI
********************

You can install the iorodeo-potentiostat library from `PyPi`_ using pip as follows:

.. code-block:: bash

  $ pip install iorodeo-potentiostat


If you are installing using pip then all required dependencies should
automatically be downloaded and installed when running this command.


**********************
Installing from source
**********************

An alternative installation method is to download and install from source. If
you would like to install in this manner the  source for the library can be
found in the `potentiostat shield repository`_.  After downloading a copy of
the repository you can install the software by running the following command in
the module's top level directory (software/python/potentiostat).


.. code-block:: bash

  $ python setup.py install

 
If your are installing from source (not with pip) then you will also need to
install the following dependencies:

* `Pyserial >= 2.6`_ 
* `Progressbar33`_ 


**********
Virtualenv
**********

If you are developing with the library it is very likely that you will want to
use `virtualenv`_ during installation. A tutorial describing how to use virtualenv
can be found here `virtualenv tutorial`_  and more detailed information can be
found in the `virtualenv documentation`_.  If you are using the library on
Windows you might want to look this additional tutorial `Python, pip and
virtuanenv on Windows`_. 


Driver (Windows Only)
=====================

On versions of windows < 10. You will need to install a driver in order to communicate with the
teensy 3.2 as a serial port. The easiest way to do this is to run the `teensyduino installer`_.

Note, this step is not required on Linux or on Mac OS.


udev rules (Linux only)
=======================
On Linux you may want to give non-root users permission to use the teensy
device. This can be done by adding the `49-teensy.rules`_ file to the
/etc/udev/rules.d directory and reloading the rules using udevadm. 

Copy to /etc/udev/rules.d as follows

.. code-block:: bash

  $ sudo cp 49-teensy.rules /etc/udev/rules.d/

Reload udev rules

.. code-block:: bash

  $ sudo udevadm control --reload-rules

**********
References
**********

.. target-notes::

.. _`PyPI`: https://pypi.python.org/pypi
.. _`potentiostat shield repository`: https://github.com/iorodeo/potentiostat/
.. _`virtualenv`: https://pypi.python.org/pypi/virtualenv
.. _`virtualenv tutorial`: http://python-guide-pt-br.readthedocs.io/en/latest/dev/virtualenvs/ 
.. _`virtualenv documentation`: https://virtualenv.pypa.io/en/stable/ 
.. _`teensyduino installer`: https://www.pjrc.com/teensy/td_download.html
.. _`49-teensy.rules`: https://www.pjrc.com/teensy/49-teensy.rules
.. _`Python, pip and virtuanenv on Windows`: http://www.tylerbutler.com/2012/05/how-to-install-python-pip-and-virtualenv-on-windows-with-powershell/
.. _`Pyserial >= 2.6`: https://pythonhosted.org/pyserial/
.. _`Progressbar33`: https://pypi.python.org/pypi/progressbar33 


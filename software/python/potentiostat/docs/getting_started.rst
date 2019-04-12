.. _getting_started_ref:

###############
Getting Started
###############

This section provides a short guide to help you begin using your Rodeostat with the 
**iorodeo-potentiostat** library.



************************
Creating a device object
************************

The first step to controlling your Rodeostat is creating a device object. In
order to do this you will need to know the name of the **port** on the computer
which is associated with the Rodeostat.  The name of this port will vary
depending on your operating system, what other devices are connected to your
computer,  etc.  On linux this port will be named something like /dev/ttyACM0,
/dev/ttyACM1, ..., etc.  On Windows it will be named something like COM1, COM2,
etc. 

A device object can be created as follows

.. code-block:: python 

  from potentiostat import Potentiostat

  pstat = Potentiostat('/dev/ttyACM0')


This will open a connection which can be used to communicate with the Rodeostat. 

.. note::

    In order to reduce repetition,  in all of the examples which follow,  we
    will assume that you have already created a Potentiostat device object,
    named pstat, using the above command.


**********************************
Getting list of voltametric tests
**********************************

A list of all of the voltammetric tests supported by the current firmware on
the Rodeostat can be obtained using the
:meth:`~potentiostat.Potentiostat.get_test_names` method.

.. code-block:: python

  test_names = pstat.get_test_names()

This method will return a list, such as that given below.

.. code-block:: python

  test_names = ['cyclic', 'sinusoid', 'constant', 'squareWave', 'linearSweep', 'chronoamp', 'multiStep']

Each string in the list is name of a voltammetric test which can be run by the
firmware on the Rodeostat.  


************************************
Getting voltammetric test parameters
************************************

The current parameter values used for a particular voltammetric test are stored
in memory on the potentiostat.  You can retrieve the current values for these
parameters from the device using the :meth:`~potentiostat.Potentiostat.get_param` method. 

For example, you can  get the current parameter values for the linearSweep test using 
the following command.

.. code-block:: python

  param = pstat.get_param('linearSweep')

This method returns a dictionary containing the all of the the parameters for
the specified test and their current values.   For example, for the  
linearSweep test result would be something like the dictionary shown below.  

.. code-block:: python

  param = {'quietTime': 0, 'quietValue': 0.0, 'finalValue': 0.5, 'startValue': -0.5, 'duration': 2000}

In the above output all time values, such as quietTime and duration, are given
in (ms) and all output voltages, such as quietValue, startValue and finalValue,
are given in (V).  For a complete description of the parameters for all
voltammetric see the :ref:`tests_ref` section of the documentation.



.. _getting_started_set_param_ref:

************************************
Setting voltammetric test parameters
************************************

The :meth:`~potentiostat.Potentiostat.set_param` method can be used to set the
parameters used for a specific voltammetric test. The parameters are stored in
RAM (voltile memory) on the Rodeostat. They will retain their value, for the
specified test,  as long as the Rodeostat has power or until changed via
another call to the :meth:`~potentiostat.Potentiostat.set_param` method.

The following example  demonstrates how to set the parameters for the *linearSweep* test.

.. code-block:: python

  param = {'quietTime': 0, 'quietValue': 0.0, 'finalValue': 0.5, 'startValue': -0.5, 'duration': 2000}

  pstat.set_param('linearSweep',param)
  
In the param dictionary above all time values, such as quietTime and duration,
are given in (ms) and all output voltages, such as quietValue, startValue and
finalValue, are given in (V).  For a complete description of the parameters for
all voltammetric see the :ref:`tests_ref` section of the documentation.

.. note::

  The parameter values for all voltammetric test are stored in volatile memory.
  Because of this, after a power cycle of the Rodeostat,  all parameters will
  revert to their default  values. 

*****************************************
Getting/setting measurement current range
*****************************************

The Rodeostat has four programmable current measurement ranges. The
exact values for the avialable ranges is determined by the hardware variant of
the device you are using. The library will automatically
detect the hardware variant of the device for you and you can retrieve  the
current ranges available on your device using the
:meth:`~potentiostat.Potentiostat.get_all_curr_range` method. 

.. code-block:: python

  curr_range_list = pstat.get_all_curr_range()


This will return a list of strings representing the available current ranges
such as that given below.

.. code-block:: python

  curr_range_list = ['1uA', '10uA', '100uA', '1000uA']


To get the current measurement range which your device is currently using 
you can use the the :meth:`~potentiostat.Potentiostat.get_curr_range` method. 

.. code-block:: python

  curr_range = pstat.get_curr_range()

This will return a string representation of the current measurement range. 

.. code-block:: python

  curr_range = '10uA'


In order to set the desired current measurement range on your device you can
use the :meth:`~potentiostat.Potentiostat.set_curr_range` method. For example,
to change the current range to 100uA you could do the following.

.. code-block:: python

  pstat.set_curr_range('100uA')


.. note::

    All current ranges supported by the device are bipolar and  measure both
    positive and negative currents. For example, the 10uA current
    range can measure current in the range -10uA to +10uA. 


***************************
Getting/setting sample rate
***************************
When running a test the device returns measurements at a specified rate
(samples/sec) for the duration of the test.  You can use the
:meth:`~potentiostat.Potentiostat.get_sample_rate` method to retrieve the
current value of sample rate used for measurements. 

.. code-block:: python

  sample_rate = pstat.get_sample_rate()

This method will return the current sample rate, in samples/sec, as floating
point number.

If you want to change the sample rate used for measurements you can use the
:meth:`~potentiostat.Potentiostat.set_sample_rate` method. For example, to set the
current sample rate to 50 samples/sec you would do the following.

.. code-block:: python

  pstat.set_sample_rate(50.0)



As an alternative you can also set/get the time between samples or sample
period.  The sample period will alwasy be equal to 1/sample_rate.  The
:meth:`~potentiostat.Potentiostat.get_sample_period` method returns the
sample_period in seconds.

.. code-block:: python

   sample_period = pstat.get_sample_period()


Similarly, the :meth:`~potentiostat.Potentiostat.set_sample_period` method sets
the sample period (given in seconds). 

.. code-block:: python

   pstat.set_sample_period(0.02)


***************************
Running  voltammetric tests
***************************

Voltammetric tests can be run using the
:meth:`~potentiostat.Potentiostat.run_test` method. For example, in order to
run the cyclic voltammetry test you could do the following. 

.. code-block:: python

   t, volt, curr = pstat.run_test('cyclic')


This method will return lists which contain the measurement times (s), voltages (V) and
currents (uA) respectively.  The test will be run with the parameter values
set in the potentiostat's memory for the specified test. 

This method takes several optional keyword arguments. For example, if you want
to save the data to a file while the test proceeds you can specify the file name 
using the *filename* keyword. 

.. code-block:: python

   t, volt, curr = pstat.run_test('cyclic', filename='data.txt')


The *param* keyword argument lets you specify the value of the parameters to
use for the test. In this case the parameter values will first be set to the
values specified and then the Rodeostat will run the test.


.. code-block:: python

    my_param = {
            'quietValue' : 0.0,
            'quietTime'  : 1000,
            'amplitude'  : 2.0,
            'offset'     : 0.0,
            'period'     : 1000,
            'numCycles'  : 5,
            'shift'      : 0.0,
            }

   t, volt, curr = pstat.run_test('cyclic', param=my_param)


For more complete documentation on the
:meth:`~potentiostat.Potentiostat.run_test` method see the :ref:`api_ref`
section.  For a more complete description of the various voltammetric tests see
:ref:`tests_ref` section. 

.. note::

  Note, when running tests with the :meth:`~potentiostat.Potentiostat.run_test`
  method the output voltage range is automatically be selected by the firmware
  prior to running the test. Thus you do not need to specifically select the
  output voltage range before using this method. 


****************************
Setting output voltage range
****************************


Under certain circumstances, such as when using manual/direct control rather
than a pre-programmed test proceedure,  you may want set the output voltage
range of the Rodeostat directly. This can be done using the
:meth:`~potentiostat.Potentiostat.set_volt_range` method.

You can retrieve the list of available output voltage ranges supported by the
device using the :meth:`~potentiostat.Potentiostat.get_all_volt_range` method.

.. code-block:: python

  volt_range_list = pstat.get_all_volt_range()

This will return a list of strings representing the available voltage ranges like that below

.. code-block:: python

  volt_range_list = ['1V', '2V', '5V', '10V']


To set set the voltage range you can use the
:meth:`~potentiostat.Potentiostat.set_volt_range` method.  For example, to set
the voltage range to '2V' you would do the following. 

.. code-block:: python

    pstat.set_volt_range('2V')


.. note::

   The output voltage ranges supported by the potentiostat are bipolar i.e., they
   including both negative and positive voltages. For example the 2V voltage
   range allows output voltages from -2V to +2V. 


***********************
Manual/direct operation
***********************

When operating the potentiostat manually you set the output voltage directly
using the :meth:`~potentiostat.Potentiostat.set_volt` method rather than using
a pre-programmed voltammetric test. For example, the following command will set
the output voltage (potential between working and reference electrodes) to 0.75V


.. code-block:: python

  pstat.set_volt(0.75)

The potentiostat will maintain this output voltage  until you change it with
another call to :meth:`~potentiostat.Potentiostat.set_volt` or you run a test
with the :meth:`~potentiostat.Potentiostat.run_test` method.  In a similar
manner, during manual operation,  you can use the
:meth:`~potentiostat.Potentiostat.get_curr` method to get a single immediate
measurement of the current  

.. code-block:: python

  curr = pstat.get_curr()

The current is returned as floating point number with units of (uA).   

Using these two methods described above,
:meth:`~potentiostat.Potentiostat.set_volt` and
:meth:`~potentiostat.Potentiostat.get_curr`, you can easily program simple time
varying voltametric tests - provided that the timing requirements are not too
demanding.  For a more detialed example demonstrating manual control see the
:ref:`examples_ref` section.



.. note::

    Prior to operating the potentiostat manually/directly you will want to set
    the output voltage range such that it spans all voltages will will occur
    during your test.  Setting the output voltage outside of the range will
    result in clipping of the output to the maximum/minimum value in the
    voltage range.  Also, changing the output voltage range during a test is
    inadvisable as it may cause glitch in the output voltage as the Rodeostat
    switches from one range to the other. 
   


************************************
Setting device identification number
************************************

An identifying number can be assigned to the Rodeostat using the
:meth:`~potentiostat.Potentiostat.set_device_id` method. For example, the
following command will set the device identification number to 5. 

.. code-block:: python

  pstat.set_device_id(5)

This idenitfying number is stored in non-volatile memory and thus will maintain
its value even when the device loses power.  This is useful in situations where
a program controlling more than one Rodeostat at a given time and needs a
simple mechanism to disambiguate them. 

The device identification number can be read using the
:meth:`~potentiostat.Potentiostat.get_device_id` method as shown below.

.. code-block:: python

  device_id = pstat.get_device_id()


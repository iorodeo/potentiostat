.. _multiplexer_ref:

############################
Multiplexer Exapansion Board
############################

This section provides a short guide to help you begin using your Rodeostat in
conjunction with the multiplexer expansion board.  This  expansion board
enables the Rodeostat to use up to seven independent working electrodes
simultaneously. When connected to the Rodeostat additional features provided
multiplexer may accessed programmatically via the Python API. 


**********************************
Enabling/Disabling the multiplexer
**********************************

In order to use the multiplexer it must first be enabled. This can be done
using the :meth:`~potentiostat.Potentiostat.set_mux_enabled` method. To enable the 
multiplexer you would run the following command 


.. code-block:: python

  rsp = pstat.set_mux_enabled(True)



Similarly in order to disable the multiplexer you would run the command shown below

.. code-block:: python

  rsp = pstat.set_mux_enabled(False)

The response returned by the :meth:`~potentiostat.Potentiostat.set_mux_enabled`
will be either True/False indicating whether or not the multiplexer has been
successfully enabled/disabled respectively. 

***************************************
Setting the working electrode channels
***************************************

The multiplexer has seven working electrode channels. You don't need to use all
the working electrode channels and the same time. The subset of working
electrode channel which are enabled can be set using the
:meth:`~potentiostat.Potentiostat.set_enabled_mux_channels` method. For example,
the following command will enable working electrode channels 1, 3 and 7.

.. code-block:: python

  pstat.set_enabled_mux_channels([1,3,7])

To query the device for the list of currently enabled working electrode
channels you can using the
:meth:`~potentiostat.Potentiostat.get_enabled_mux_channels` method. For example
the command

.. code-block:: python

  channel_list = pstat.get_enabled_mux_channels()

In order to run a test with the multiplexer expansion board the firmware requires 
that at least one working electrode channel is enabled.  


***************************************
Running tests
***************************************

Running tests with the multiplexer expansion board enabled is almost exactly
the same as normal using the :meth:`~potentiostat.Potentiostat.run_test`
method.  For example, in order to run the cyclic voltammetry test you could do
the following. 

.. code-block:: python

   data_dict = pstat.run_test('cyclic')


The main difference is that when the multiplexer is enabled the
:meth:`~potentiostat.Potentiostat.run_test` returns a dictionary containing the
measured data for each channel rather than a tuple of times, voltages and
currents.  The keys of the dictionary returned are the enabled channel numbers
and the values are dictionaries with the time, voltage and current measurments
for that channel, keyed by 't', 'v', and 'i' respectively.  Thus the time,
voltage and current data for channel 1 can be accessed as follows.

.. code-block:: python

    chan1_time = data_dict[1]['t']  # channel 1, list of sample times 
    chan1_volt = data_dict[1]['v']  # channel 1, list of output voltages
    chan1_curr = data_dict[1]['i']  # channel 1, list of current samples 

The parameters for the test can be set as usual using the
:meth:`~potentiostat.Potentiostat.set_param` method as described here

:ref:`examples_ref`

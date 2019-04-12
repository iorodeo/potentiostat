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
:meth:`~potentiostat.Potentiostat.set_param` method as described in the
:ref:`getting_started_set_param_ref` subsection, or by specifying the
parameters using the params keyword argument to the
:meth:`~potentiostat.Potentiostat.run_test` method as shown below

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

    data_dict  = pstat.run_test('cyclic', param=my_param)



.. note::

    When using the multiplexer all electrodes (counter, reference and working)
    are on digitally controlled switches.  By default, when not running a test,
    the electrodes will be disconnected. When using the
    :meth:`~potentiostat.Potentiostat.run_test` method the electrodes will be
    automatically connected using these switches prior to running the test.
    Similarly, after the test is complete, the electrodes will be automatically
    disconnected. 


.. note::

    At this time the squareWave test is not compatible with the multiplexer
    expansion board. Attempting to run this when the multiplexer is enabled
    will result in an error. 

To get a list of the test which are compatibile with the multiplexer the 
:meth:`~potentiostat.Potentiostat.get_mux_test_names`  can be used.

.. code-block:: python
    
    test_names = pstat.get_mux_test_names()

This command will return a list such as that shown below

.. code-block:: python

  test_names = ['cyclic', 'sinusoid', 'constant', 'linearSweep', 'chronoamp', 'multiStep']


***************************************************
Manual/direct operation when the multiplexer 
***************************************************

When using the Rodeostat with the multiplexer expansion board in manual/direct
control mode a few special considerations are required.  By default all
electrodes (counter, reference and working) are disconnected and you must
manually specify in software when you want to connect a specific electrode. 
The methods used for the reference and counter electrodes this are:

    * :meth:`~potentiostat.Potentiostat.set_mux_ctr_elect_connected` which connects/disconnects the counter electrode 
    * :meth:`~potentiostat.Potentiostat.set_mux_ref_elect_connected` which connects/disconnects the reference electrode 


For example, the following commmands connect the counter and reference electrodes.

.. code-block:: python

    pstat.set_mux_ctr_elect_connected(True)   # connect the counter electrode 
    pstat.set_mux_ref_elect_connected(True)   # connect the reference electrode

Similarly, the counter and referece electrodes can be disconnected as shown below. 

.. code-block:: python

    pstat.set_mux_ctr_elect_connected(False)   # disconnect the counter electrode 
    pstat.set_mux_ref_elect_connected(False)   # disconnect the reference electrode

The enabled working electrodes are automatically connected to multiplexer. In
addition the working electrodes can be connected to current measurement
circuit (transimpedance amplifier) via the make-before-break multiplexer using the
:meth:`~potentiostat.Potentiostat.set_mux_wrk_elect_connected` method. This
command takes as an argument the number of the working electrode you would like
to connect to the measurement circuit. For example, to connect working
electrode number 3 to the current measurement circuit you would use the folling
command.

.. code-block:: python

    pstat.set_mux_wrk_elect_connected(3)  # connect working electrode number 3 to TIA 

.. note::

    Only one enabled working electrode can be connected to the
    measurement circuit at a time. For example, if working electrode number 3 is
    connected the the current measurement and you wish to connect working
    electrode 5 to this circuit you can do this by running the command 
    pstat.set_mux_wrk_elect_connected(5). This will connect working electrode 5
    to the measurement circuit. However, prior to connecting working electrode
    5, working electrode 3 will first be disconnected, using the a
    make-before-break protocol, before connecting electrode 5.


To disconnect all working electrodes from the measurement circuit the you can
run the :meth:`~potentiostat.Potentiostat.set_mux_wrk_elect_connected`  method
with an argument of False. For example, 

.. code-block:: python

    pstat.set_mux_wrk_elect_connected(False)  # disconnect all working electrodes from TIA 

.. note::

    When working electrodes are enabled the are connected electronically to the
    multiplexer (and Rodeostat). At this point the can sink/source current. The
    :meth:`~potentiostat.Potentiostat.set_mux_wrk_elect_connected` just selects
    which of the enabled working electrodes is connect to current measurent
    circuit (transimpedance amplifier) using the make-before-break protocol.


To disconnect all electrodes (counter, reference and working) with a single command the 
:meth:`~potentiostat.Potentiostat.disconnect_all_mux_elect` method  may be used as shown below.

.. code-block:: python

    pstat.disconnect_all_mux_elect()  # disconnect all electrodes 


    


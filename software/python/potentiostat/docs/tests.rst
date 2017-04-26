.. _tests_ref:


#################
Voltametric Tests 
#################

In this section we describe pre-programmed tests defined the potentiostat
shield's firmware. 

******************
Cyclic voltammetry 
******************

In cyclic voltammetry current is measured while the potential (voltage) between
the working and reference electrode is ramped up and down cyclically in piecewise
linear fashion - in a triangle waveform - for a number of cycles.  This triangle
waveform can be specified by the *amplitude*, *offset*, *period* and (phase)
*shift* in a manner similar to a sine wave.  Prior to beginning the triangle
waveform output, the  test procedure waits for a quiet period during which the
voltage is held as a user specified value. The quiet period is defined by the
*quietTime* and *quietValue* parameters.  Immediately following the end of the
quiet period the triangle waveform output begins.  The seven parameters used to
define the cyclic voltammetry test are test are summarized in the table below.

================= ========================================= =========== ========== 
 parameter         description                               units       type     
================= ========================================= =========== ========== 
  quietValue       output value during the quiet period         V         float    
  quietTime        duration of quiet period                     ms        integer   
  amplitude        peak amplitude of triangle waveform          V         float    
  offset           offset of triangle waveform from zero        V         float    
  period           period of triangle waveform                  ms        integer  
  numCycles        number of cycles to perform                  NA        integer  
  shift            unitless phase shift for waveform            NA        float    
================= ========================================= =========== ========== 

The parameters are set in the Rodeostat's firmware using the
:meth:`~potentiostat.Potentiostat.set_param` method and are passed as a
dictionary.  An example dictionary containing the parameters for the cyclic
voltammetry is shown below.

.. code-block:: python 

   {
        'quietValue' : -0.1,   # quiet period voltage (V) 
        'quietTime'  : 1000,   # quiet period duration (ms)
        'amplitude'  :  0.6,   # waveform peak amplitude (V) 
        'offset'     :  0.5,   # waveform offset (V)
        'period'     : 2000,   # waveform period (ms)
        'numCycles'  :    2,   # number of cycles
        'shift'      :  0.0,   # unitless phase shift
    }

The following figure illustrates the output voltage of the potentiostat with
these parameters. 

.. figure:: _static/cyclic_test_fig.png
   :align:  center

When the *shift* parameter is zero the triangle waveform output for the cyclic
voltammetry test  will start at the minimum value.  This behaviour can be
changed by entering a value for the *shift* parameter in the range [0,1].  The
periodic triangle waveform will then be shifted forward (in time) by and amount
equal to *shift x period*. Thus a shift value of 1/4 would shift the triangle
waveform a quarter of a cycle forward, a shift value of 1/2 would shift the
triangle waveform a half a cycle forward, etc. An example demonstrating the effect
of the shift parameter is shown below.  


.. figure:: _static/cyclic_shift_fig.png
   :align:  center


.. note::

    Sometimes the output waveform for cyclic voltammetry specified using the *scan
    rate* (V/s) and the *maximum/minimum voltage* values in the waveform. The
    relationship between these values and the *amplitude*, *offset* and *period* as are
    as follows:
    
    * scan rate = 4 x amplitude/period
    * maximum voltage = offset + amplitude
    * minimum voltage = offset - amplitude

More information on cyclic voltammetry can be found here `https://en.wikipedia.org/wiki/Cyclic_voltammetry`_

************************
Linear sweep voltammetry
************************

In linear sweep voltammetry current is measured while the potential between the
working and reference electrode sweeps linearly over a some range.  The range
is specified by a starting value, *startValue*, a final value, *finalValue*,
and a *duration*.  Prior to beginning the linear sweep, the test
procedure waits for a quiet period during which the voltage is held as a user
specified value.  The quiet period is specified by the quietTime and quietValue
parameters. The five parameters used to define the linear sweep voltammetry
test are test are summarized in the table below.


================= ========================================= =========== ========== 
 parameter         description                               units       type     
================= ========================================= =========== ========== 
  quietValue       output value during the quiet period         V         float    
  quietTime        duration of quiet period                     ms        integer   
  startValue       linear sweep starting value                  V         float
  finalValue       linear sweep final value                     V         float
  duration         linear sweep duration                        ms        integer
================= ========================================= =========== ========== 


The parameters are set in the Rodeostat's firmware using the
:meth:`~potentiostat.Potentiostat.set_param` method and are passed as a
dictionary.  An example dictionary containing the five parameters for the
linear sweep voltammetry is shown below. 

.. code-block:: python 

    { 
        'quietTime'  : 2000,   # quiet period voltage (V) 
        'quietValue' :  0.0,   # quiet period duration (ms)
        'startValue' : -0.8,   # linear sweep starting value (V)
        'finalValue' :  1.2,   # linear sweep final value (V)
        'duration'   : 8000,   # linear sweep duration (ms)
    }

The following figure illustrates the output voltage of the potentiostat with
these parameters. 

.. figure:: _static/linear_sweep_fig.png
   :align:  center


Additional information on linear sweep voltammetry can be found here 
`https://en.wikipedia.org/wiki/Linear_sweep_voltammetry`_

*****************
Constant voltage
*****************

================= ========================================= =========== ========== 
 parameter         description                               units       type     
================= ========================================= =========== ========== 
  quietValue       output value during the quiet period         V         float    
  quietTime        duration of quiet period                     ms        integer   
  value            output value during the test period          V         float
  duration         duration of the test period                  ms        integer
================= ========================================= =========== ========== 

| 

.. code-block:: python 

    {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'value'      : 1.0,
        'duration'   : 5000,
    }


**********************
Sinusoidal voltammetry
**********************

================= =========================================== =========== ========== 
 parameter         description                                  units       type     
================= =========================================== =========== ========== 
  quietValue       output value during the quiet period           V         float    
  quietTime        duration of quiet period                       ms        integer   
  amplitude        peak amplitude of sinusoid waveform            V         float    
  offset           offset of sinusoid waveform from zero          V         float    
  period           period of sinusoid waveform                    ms        integer  
  numCycles        number of cycles to perform                    NA        integer  
  shift            unitless phase shift for waveform              NA        float    
================= =========================================== =========== ========== 

|

.. code-block:: python 

    {
        'quietValue' : 0.0,
        'quietTime'  : 0,
        'amplitude'  : 2.0,
        'offset'     : 0.0,
        'period'     : 2000,
        'numCycles'  : 3,
        'shift'      : 0.0,
    }

*****************
Chronoamperometry
*****************

================= ================================================= =============== ====================== 
 parameter         description                                         units           type     
================= ================================================= =============== ====================== 
  quietValue       output value during the quiet period                  V             float    
  quietTime        duration of quiet period                              ms            integer   
  step             list (len=2) of (duration,value) tuples             (ms, V)         (integer, float)
================= ================================================= =============== ====================== 

|

.. code-block:: python 

    {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'step'       : [(1000,-0.25), (1000,0.5)],
    }


*********************
Multistep voltammetry
*********************

================= ================================================= =============== ====================== 
 parameter         description                                         units           type     
================= ================================================= =============== ====================== 
  quietValue       output value during the quiet period                  V             float    
  quietTime        duration of quiet period                              ms            integer   
  step             list (len=<50) of (duration,value) tuples             (ms, V)         (integer, float)
================= ================================================= =============== ====================== 

|

.. code-block:: python 

    {
        'quietValue' : 0.0,
        'quietTime'  : 1000,
        'step'       : [(1000,-0.5), (1000,-0.2), (1000,-0.3), (1000,-0.0), (1000,-0.1), (1000,0.3), (1000,0.2), (1000, 0.5)],
    }

**********
References
**********

.. target-notes::

.. _`https://en.wikipedia.org/wiki/Cyclic_voltammetry`: https://en.wikipedia.org/wiki/Cyclic_voltammetry 
.. _`https://en.wikipedia.org/wiki/Linear_sweep_voltammetry`: https://en.wikipedia.org/wiki/Linear_sweep_voltammetry



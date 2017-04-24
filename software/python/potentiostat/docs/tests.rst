.. _tests_ref:


#################
Voltametric Tests 
#################

In this section we describe pre-programmed tests defined the potentiostat
shield's firmware. 

******************
Cyclic voltammetry 
******************

In cyclic voltammetry the output voltage ramps up and down cyclically in
piecewise linear fashion in a triangle waveform for a number of cycles.  This
triangle waveform can be specified by the *amplitude*, *offset*, *period* and (phase)
*shift* in a manner similar to a sinewave.  Prior to begining the triangle
waveform output, the  test procedure waits for a quiet period during which the
voltage is held as a user specified value. The quiet period is defined by the
*quietTime* and *quietValue* parameters.  Immediately following the end of the
quiet period the triangle waveform output begins.  The seven parameters used to
define the cyclic voltammetry test are test are summarized in the table below.

================= ========================================= =========== ========== 
 parameter         description                               units       type     
================= ========================================= =========== ========== 
  quietValue       output during the quiet period               V         float    
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

For this examle dictionary voltage output would be as shown in the figrue below. 

.. figure:: _static/cyclic_test_fig.png
   :align:  center

.. note::

    Sometimes the output waveform for cyclic voltammetry specified using the *scan
    rate* (V/s) and the *maximum/minimum voltage* values in the waveform. The
    relationship between these values and the *amplitude*, *offset* and *period* as are
    as follows:
    
    * scan rate = 4 x amplitude/period
    * maximum voltage = offset + amplitude
    * minimum voltage = offset - amplitude



The voltage output for these parameters is shown in the figure below. 



`cyclic voltammetry`_ 

**********************
Sinusoidal voltammetry
**********************

************************
Linear sweep voltammetry
************************

*****************
Constant voltage
*****************

*****************
Chronoamperometry
*****************

*********************
Multistep voltammetry
*********************


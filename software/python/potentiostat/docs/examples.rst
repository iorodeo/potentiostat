.. _examples_ref:

###############
Worked Examples
###############

In this section we show several worked examples demonstrating how to use iorodeo-potentiostat library
to make measurements. 

.. note::

   The examples in this section make use of the `Matplotlib`_ plotting library.
   You can find Instructions for installing maplotlib can be found here:
   `installing Matplotlib`_.


******************
Cyclic Voltammetry
******************

Suppose we want to run a `cyclic voltammetry`_ test with the following parameters:

* Starts at a minimum voltage of -0.1 V
* Reaches a maximum voltage of 1.0 V
* Transistions from the minimum voltage to the maximum voltage at a rate of 50 mV/s. 
* Peforms a single cycle i.e., transistions for minimum -> maximum -> minimum.

.. literalinclude:: ../examples/run_cyclic_w_plot.py
   :language: python 
   


****************************
Constant Voltage Voltammetry
****************************


*********************
Manual/Direct Control
*********************


**********
References
**********

.. target-notes::

.. _`Matplotlib`: http://matplotlib.org/ 
.. _`installing Matplotlib`: http://matplotlib.org/users/installing.html 
.. _`cyclic voltammetry`: https://en.wikipedia.org/wiki/Cyclic_voltammetry

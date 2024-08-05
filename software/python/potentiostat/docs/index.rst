.. iorodeo-potentiostat documentation master file, created by
   sphinx-quickstart on Fri Mar 24 10:38:13 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

####################
iorodeo-potentiostat  
####################

A Python library for controlling IO Rodeo's Rodeostat open source potentiostat





.. figure:: _static/rodeostat_v0p2_pcb.png
   :align:  center

IO Rodeo's Rodeostat is an open source potentiostat for performing
electrochemical measurments which is designed to work with the `teensy 3.2
development board <https://www.pjrc.com/teensy/teensy31.html>`_. 
The **iorodeo-potentiostat** library provides a simple highlevel intreface for
controlling the Rodeostat allowing users to easily:  

* set/get the parameters used for the voltammetric tests
* run voltammetric tests and collect data from the device (time, voltage, current)
* set/get the output voltage and current measurement ranges
* set/get the sample rate/period used for measurements


To quickly get up and running using the library see the :ref:`getting_started_ref` guide.
For a more comprehensive coverage of the API provided by the library see the :ref:`api_ref`.


Contents:

.. toctree::
    :maxdepth: 2

    installation
    getting_started
    multiplexer
    examples
    tests 
    api_reference
    hardware
    json


******************
Indices and tables
******************

* :ref:`genindex`
* :ref:`modindex`
* :ref:`search`


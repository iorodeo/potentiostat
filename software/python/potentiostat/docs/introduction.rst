
Introduction
============

.. figure:: _static/pstat_shield_img_0.JPG
   :align:  center

IO Rodeo's Potentiostat Shield is an open source potentiostat for performing
electrochemical measurments which is designed to work with the `teensy 3.2
development board <https://www.pjrc.com/teensy/teensy31.html>`_. 

The **iorodeo-potentiostat** Python library provides a simple highlevel intreface for
controlling the potentiostat shield allowing users to easily:  

* set/get the parameters used for the voltammetric tests
* run voltammetric tests and collect data from the device (time, voltage, current)
* set/get the output voltage and current measurement ranges
* set/get the sample rate/period used for measurements


To quickly get up and running using the library see the Getting Started guide.
For a more comprehensive coverage of the API provided by the library see the
API Reference.

A brief summary of the Potentiostat Shield's capabilites is given below.

* teensy 3.2 (32-bit ARM Cortex-M4 72 MHz CPU, 256k Flash, 64k RAM, 2K EEPROM)
* 12-bit voltage output with four available ranges:   ±1, 2, 5, 10V
* 16-bit current measurement with four available ranges: ±1, 10, 100, 1000uA
* Controlled over USB using simple JSON messages  
* Can be programmed over USB using the Arduino IDE (`teensyduino <https://www.pjrc.com/teensy/td_download.html>`_).  
* Expansion headers with DIO, analog inputs, UART, I2C, and SPI 
* Firmware supports many standard voltammetric methods including:
    * constant voltage
    * cyclic voltammetry
    * sinusoidal voltammetry 
    * linear sweep voltammetry
    * chronoamperometry
    * multistep

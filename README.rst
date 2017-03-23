IO Rodeo Potentiostat Shield
============================

Software, firmware and hardware designs files for IO Rodeo's Potentiostat Shield.  

| 

.. figure:: /images/pstat_shield_img_0.JPG
    :scale: 100 %
    :alt: alternate text
    :align: center

Hardware:
---------

* Designed as a shield for  `teensy 3.2 development board <https://www.pjrc.com/teensy/teensy31.html>`_.   
* 12-bit voltage output with four range settings:  +/- 1, 2, 5, 10V
* 16-bit current measurement with four  range settings: +/- 1, 10, 100, 1000 uA ranges
* Can be programmed over USB using the Arduino IDE (`teensyduino <https://www.pjrc.com/teensy/td_download.html>`_)  
* Expansion headers with DIO, analog inputs, UART, I2C, and SPI 

Firware:
---------
* Implements many standard voltammetric methods including: contant voltage, cyclic voltammetery, linearsweep, chronoamperometry, multistep. 
* Easy to extend enabling users to add custom tests. 
* Simple API for controlling the device over USB/Serial using messages in JSON. 

Software:
---------
* Python libray implementing Serial API providing easy high level control of the device.

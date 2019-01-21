EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:adapter-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "16 jan 2019"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_5X2 P1
U 1 1 5C3EA35D
P 2150 1450
F 0 "P1" H 2150 1750 60  0000 C CNN
F 1 "CONN_5X2" V 2150 1450 50  0000 C CNN
F 2 "" H 2150 1450 60  0000 C CNN
F 3 "" H 2150 1450 60  0000 C CNN
	1    2150 1450
	1    0    0    -1  
$EndComp
$Comp
L CONN_3 K1
U 1 1 5C3EA406
P 4700 1350
F 0 "K1" V 4650 1350 50  0000 C CNN
F 1 "CONN_3" V 4750 1350 40  0000 C CNN
F 2 "" H 4700 1350 60  0000 C CNN
F 3 "" H 4700 1350 60  0000 C CNN
	1    4700 1350
	1    0    0    -1  
$EndComp
$Comp
L CONN_7 P2
U 1 1 5C3EA415
P 4700 2000
F 0 "P2" V 4670 2000 60  0000 C CNN
F 1 "CONN_7" V 4770 2000 60  0000 C CNN
F 2 "" H 4700 2000 60  0000 C CNN
F 3 "" H 4700 2000 60  0000 C CNN
	1    4700 2000
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1250 4150 1250
Wire Wire Line
	4350 1350 4150 1350
Wire Wire Line
	4350 1450 4150 1450
Wire Wire Line
	4350 1700 4150 1700
Wire Wire Line
	4350 1800 4150 1800
Wire Wire Line
	4350 1900 4150 1900
Wire Wire Line
	4350 2000 4150 2000
Wire Wire Line
	4350 2100 4150 2100
Wire Wire Line
	4350 2200 4150 2200
Wire Wire Line
	4350 2300 4150 2300
Text Label 4150 1250 2    60   ~ 0
GND
Text Label 4150 1350 2    60   ~ 0
CTR_SW
Text Label 4150 1450 2    60   ~ 0
REF_SW
Text Label 4150 1700 2    60   ~ 0
WRK_1
Text Label 4150 1800 2    60   ~ 0
WRK_2
Text Label 4150 1900 2    60   ~ 0
WRK_3
Text Label 4150 2000 2    60   ~ 0
WRK_4
Text Label 4150 2100 2    60   ~ 0
WRK_5
Text Label 4150 2200 2    60   ~ 0
WRK_6
Text Label 4150 2300 2    60   ~ 0
WRK_7
Text Notes 3650 2550 0    60   ~ 0
Screw Terminal Electrode Connections
Wire Wire Line
	1750 1250 1550 1250
Wire Wire Line
	1750 1350 1550 1350
Wire Wire Line
	1750 1450 1550 1450
Wire Wire Line
	1750 1550 1550 1550
Wire Wire Line
	1750 1650 1550 1650
Wire Wire Line
	2550 1250 2750 1250
Wire Wire Line
	2550 1350 2750 1350
Wire Wire Line
	2550 1450 2750 1450
Wire Wire Line
	2550 1550 2750 1550
Wire Wire Line
	2550 1650 2750 1650
Text Label 1550 1250 2    60   ~ 0
GND
Text Label 2750 1250 0    60   ~ 0
CTR_SW
Text Label 1550 1350 2    60   ~ 0
REF_SW
Text Label 2750 1350 0    60   ~ 0
WRK_1
Text Label 1550 1450 2    60   ~ 0
WRK_2
Text Label 2750 1450 0    60   ~ 0
WRK_3
Text Label 1550 1550 2    60   ~ 0
WRK_4
Text Label 2750 1550 0    60   ~ 0
WRK_5
Text Label 1550 1650 2    60   ~ 0
WRK_6
Text Label 2750 1650 0    60   ~ 0
WRK_7
Text Notes 1600 1850 0    60   ~ 0
Connection Header (to mux)
$EndSCHEMATC

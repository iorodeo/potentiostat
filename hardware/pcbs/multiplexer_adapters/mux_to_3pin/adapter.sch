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
Date "18 jan 2019"
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
Text Notes 3950 4450 0    60   ~ 0
Electrode Connections
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
$Comp
L CONN_3 K1
U 1 1 5C4127DC
P 4700 1350
F 0 "K1" V 4650 1350 50  0000 C CNN
F 1 "CONN_3" V 4750 1350 40  0000 C CNN
F 2 "" H 4700 1350 60  0000 C CNN
F 3 "" H 4700 1350 60  0000 C CNN
	1    4700 1350
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1250 4150 1250
Wire Wire Line
	4350 1350 4150 1350
Wire Wire Line
	4350 1450 4150 1450
Text Label 4150 1250 2    60   ~ 0
CTR_SW
Text Label 4150 1350 2    60   ~ 0
REF_SW
Text Label 4150 1450 2    60   ~ 0
WRK_1
$Comp
L CONN_3 K2
U 1 1 5C4128F5
P 4700 1800
F 0 "K2" V 4650 1800 50  0000 C CNN
F 1 "CONN_3" V 4750 1800 40  0000 C CNN
F 2 "" H 4700 1800 60  0000 C CNN
F 3 "" H 4700 1800 60  0000 C CNN
	1    4700 1800
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 1700 4150 1700
Wire Wire Line
	4350 1800 4150 1800
Wire Wire Line
	4350 1900 4150 1900
Text Label 4150 1700 2    60   ~ 0
CTR_SW
Text Label 4150 1800 2    60   ~ 0
REF_SW
Text Label 4150 1900 2    60   ~ 0
WRK_2
$Comp
L CONN_3 K3
U 1 1 5C412901
P 4700 2250
F 0 "K3" V 4650 2250 50  0000 C CNN
F 1 "CONN_3" V 4750 2250 40  0000 C CNN
F 2 "" H 4700 2250 60  0000 C CNN
F 3 "" H 4700 2250 60  0000 C CNN
	1    4700 2250
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2150 4150 2150
Wire Wire Line
	4350 2250 4150 2250
Wire Wire Line
	4350 2350 4150 2350
Text Label 4150 2150 2    60   ~ 0
CTR_SW
Text Label 4150 2250 2    60   ~ 0
REF_SW
Text Label 4150 2350 2    60   ~ 0
WRK_3
$Comp
L CONN_3 K4
U 1 1 5C41290D
P 4700 2700
F 0 "K4" V 4650 2700 50  0000 C CNN
F 1 "CONN_3" V 4750 2700 40  0000 C CNN
F 2 "" H 4700 2700 60  0000 C CNN
F 3 "" H 4700 2700 60  0000 C CNN
	1    4700 2700
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 2600 4150 2600
Wire Wire Line
	4350 2700 4150 2700
Wire Wire Line
	4350 2800 4150 2800
Text Label 4150 2600 2    60   ~ 0
CTR_SW
Text Label 4150 2700 2    60   ~ 0
REF_SW
Text Label 4150 2800 2    60   ~ 0
WRK_4
$Comp
L CONN_3 K5
U 1 1 5C412919
P 4700 3150
F 0 "K5" V 4650 3150 50  0000 C CNN
F 1 "CONN_3" V 4750 3150 40  0000 C CNN
F 2 "" H 4700 3150 60  0000 C CNN
F 3 "" H 4700 3150 60  0000 C CNN
	1    4700 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3050 4150 3050
Wire Wire Line
	4350 3150 4150 3150
Wire Wire Line
	4350 3250 4150 3250
Text Label 4150 3050 2    60   ~ 0
CTR_SW
Text Label 4150 3150 2    60   ~ 0
REF_SW
Text Label 4150 3250 2    60   ~ 0
WRK_5
$Comp
L CONN_3 K6
U 1 1 5C412925
P 4700 3600
F 0 "K6" V 4650 3600 50  0000 C CNN
F 1 "CONN_3" V 4750 3600 40  0000 C CNN
F 2 "" H 4700 3600 60  0000 C CNN
F 3 "" H 4700 3600 60  0000 C CNN
	1    4700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3500 4150 3500
Wire Wire Line
	4350 3600 4150 3600
Wire Wire Line
	4350 3700 4150 3700
Text Label 4150 3500 2    60   ~ 0
CTR_SW
Text Label 4150 3600 2    60   ~ 0
REF_SW
Text Label 4150 3700 2    60   ~ 0
WRK_6
$Comp
L CONN_3 K7
U 1 1 5C412931
P 4700 4050
F 0 "K7" V 4650 4050 50  0000 C CNN
F 1 "CONN_3" V 4750 4050 40  0000 C CNN
F 2 "" H 4700 4050 60  0000 C CNN
F 3 "" H 4700 4050 60  0000 C CNN
	1    4700 4050
	1    0    0    -1  
$EndComp
Wire Wire Line
	4350 3950 4150 3950
Wire Wire Line
	4350 4050 4150 4050
Wire Wire Line
	4350 4150 4150 4150
Text Label 4150 3950 2    60   ~ 0
CTR_SW
Text Label 4150 4050 2    60   ~ 0
REF_SW
Text Label 4150 4150 2    60   ~ 0
WRK_7
NoConn ~ 1750 1250
$EndSCHEMATC

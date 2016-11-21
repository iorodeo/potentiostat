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
LIBS:dummy_cell-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "21 nov 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_3 K1
U 1 1 58331C48
P 4400 2050
F 0 "K1" V 4350 2050 50  0000 C CNN
F 1 "CONN_3" V 4450 2050 40  0000 C CNN
F 2 "" H 4400 2050 60  0000 C CNN
F 3 "" H 4400 2050 60  0000 C CNN
	1    4400 2050
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 58331C9F
P 2050 1650
F 0 "R3" V 2130 1650 40  0000 C CNN
F 1 "R" V 2057 1651 40  0000 C CNN
F 2 "~" V 1980 1650 30  0000 C CNN
F 3 "~" H 2050 1650 30  0000 C CNN
	1    2050 1650
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 58331CAE
P 2050 2450
F 0 "R2" V 2130 2450 40  0000 C CNN
F 1 "R" V 2057 2451 40  0000 C CNN
F 2 "~" V 1980 2450 30  0000 C CNN
F 3 "~" H 2050 2450 30  0000 C CNN
	1    2050 2450
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 58331CBD
P 1750 3300
F 0 "R1" V 1830 3300 40  0000 C CNN
F 1 "R" V 1757 3301 40  0000 C CNN
F 2 "~" V 1680 3300 30  0000 C CNN
F 3 "~" H 1750 3300 30  0000 C CNN
	1    1750 3300
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 58331CCC
P 2350 3300
F 0 "C1" H 2350 3400 40  0000 L CNN
F 1 "C" H 2356 3215 40  0000 L CNN
F 2 "~" H 2388 3150 30  0000 C CNN
F 3 "~" H 2350 3300 60  0000 C CNN
	1    2350 3300
	1    0    0    -1  
$EndComp
Text Label 3850 1950 0    60   ~ 0
CTR
Text Label 3850 2050 0    60   ~ 0
REF
Text Label 3850 2150 0    60   ~ 0
WRK
Wire Wire Line
	3000 1950 4050 1950
Wire Wire Line
	2050 2050 4050 2050
Wire Wire Line
	3000 2150 4050 2150
Wire Wire Line
	1750 3550 1750 3700
Wire Wire Line
	1750 3700 2350 3700
Wire Wire Line
	2350 3700 2350 3500
Wire Wire Line
	1750 3050 1750 2900
Wire Wire Line
	1750 2900 2350 2900
Wire Wire Line
	2350 2900 2350 3100
Wire Wire Line
	2050 2700 2050 2900
Connection ~ 2050 2900
Wire Wire Line
	2050 1900 2050 2200
Connection ~ 2050 2050
Wire Wire Line
	2050 1400 2050 1200
Wire Wire Line
	2050 1200 3000 1200
Wire Wire Line
	3000 1200 3000 1950
Wire Wire Line
	2050 3700 2050 4000
Wire Wire Line
	2050 4000 3000 4000
Wire Wire Line
	3000 4000 3000 2150
Connection ~ 2050 3700
$EndSCHEMATC

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
LIBS:teensy3
LIBS:op07
LIBS:zxre060
LIBS:ad8250
LIBS:lt1995
LIBS:mea1d05xxsc
LIBS:potentiostat-cache
EELAYER 27 0
EELAYER END
$Descr User 12000 11000
encoding utf-8
Sheet 1 1
Title ""
Date "14 may 2016"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L TEENSY3.1 U?
U 1 1 5733FC56
P 2900 2225
F 0 "U?" H 2900 3575 60  0000 C CNN
F 1 "TEENSY3.1" H 2900 575 60  0000 C CNN
F 2 "~" H 2600 2425 60  0000 C CNN
F 3 "~" H 2600 2425 60  0000 C CNN
	1    2900 2225
	1    0    0    -1  
$EndComp
Wire Wire Line
	3900 1025 4100 1025
Text Label 4100 1025 0    60   ~ 0
DAC_UNI
Wire Wire Line
	1850 3625 1650 3625
Text Label 1650 3625 2    60   ~ 0
AGND
$Comp
L ZXRE060 U?
U 1 1 57352FD2
P 2800 9300
F 0 "U?" H 2800 9050 60  0000 C CNN
F 1 "ZXRE060" H 2800 9550 60  0000 C CNN
F 2 "~" H 2800 9300 60  0000 C CNN
F 3 "~" H 2800 9300 60  0000 C CNN
	1    2800 9300
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 57352FF0
P 2100 9550
F 0 "C?" H 2100 9650 40  0000 L CNN
F 1 "0.1uF" H 2106 9465 40  0000 L CNN
F 2 "~" H 2138 9400 30  0000 C CNN
F 3 "~" H 2100 9550 60  0000 C CNN
	1    2100 9550
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 57352FFF
P 2850 9850
F 0 "R?" V 2930 9850 40  0000 C CNN
F 1 "1k" V 2857 9851 40  0000 C CNN
F 2 "~" V 2780 9850 30  0000 C CNN
F 3 "~" H 2850 9850 30  0000 C CNN
	1    2850 9850
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 57353049
P 1850 9550
F 0 "C?" H 1850 9650 40  0000 L CNN
F 1 "1uF" H 1856 9465 40  0000 L CNN
F 2 "~" H 1888 9400 30  0000 C CNN
F 3 "~" H 1850 9550 60  0000 C CNN
	1    1850 9550
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 9350 1850 9300
Wire Wire Line
	1850 9750 1850 10000
Text Label 1600 9850 2    60   ~ 0
3V3
Wire Wire Line
	3900 1325 4100 1325
Text Label 4100 1325 0    60   ~ 0
3V3
Wire Wire Line
	1600 9300 2350 9300
Connection ~ 1850 9300
Text Label 1600 9300 2    60   ~ 0
AGND
Wire Wire Line
	3250 9200 3700 9200
Wire Wire Line
	3450 9200 3450 10000
Wire Wire Line
	3250 9400 3450 9400
Connection ~ 2100 9300
Wire Wire Line
	2100 9750 2100 9850
Wire Wire Line
	1600 9850 2600 9850
Wire Wire Line
	2300 9400 2300 9850
Wire Wire Line
	2300 9400 2350 9400
Wire Wire Line
	2100 9350 2100 9300
Wire Wire Line
	2250 9300 2250 9200
Wire Wire Line
	2250 9200 2350 9200
Connection ~ 2250 9300
Connection ~ 3450 9400
Wire Wire Line
	3450 9850 3100 9850
Wire Wire Line
	3450 10000 1850 10000
Connection ~ 3450 9850
Connection ~ 2100 9850
Connection ~ 2300 9850
Connection ~ 3450 9200
Text Label 3700 9200 0    60   ~ 0
REF_0V6
Text Notes 950  8800 0    60   ~ 0
Voltage Reference, 0.6V, Tol. 0.5%. Used in when shifting DAC_UNI to DAC_BIP.
Text Notes 725  4700 0    60   ~ 0
Shifts and scales unipolar DAC (DAC_UNI) from [0V,1.2V] range to bipolar DAC (DAC_BIP) in [-1V,1V]  range. \n 
$Comp
L AD8250 U?
U 1 1 573637D1
P 3725 7700
F 0 "U?" H 3725 8050 60  0000 C CNN
F 1 "AD8250" H 3725 7300 60  0000 C CNN
F 2 "~" H 3575 7700 60  0000 C CNN
F 3 "~" H 3575 7700 60  0000 C CNN
	1    3725 7700
	1    0    0    -1  
$EndComp
Wire Wire Line
	1850 1125 1650 1125
Wire Wire Line
	1850 1225 1650 1225
Text Label 1650 1125 2    60   ~ 0
DAC_GAIN_A0
Text Label 1650 1225 2    60   ~ 0
DAC_GAIN_A1
Wire Wire Line
	3225 7800 3025 7800
Wire Wire Line
	3225 7900 3025 7900
Text Label 3025 7800 2    60   ~ 0
DAC_GAIN_A0
Text Label 3025 7900 2    60   ~ 0
DAC_GAIN_A1
Wire Wire Line
	3225 7700 3025 7700
Wire Wire Line
	4225 7700 4425 7700
Text Label 3025 7700 2    60   ~ 0
-12V
Text Label 4425 7700 0    60   ~ 0
+12V
Wire Wire Line
	3900 1225 4100 1225
Text Label 4100 1225 0    60   ~ 0
GND
Wire Wire Line
	4225 7900 4425 7900
Text Label 4425 7900 0    60   ~ 0
-12V
Wire Wire Line
	4225 7800 4425 7800
Text Label 4425 7800 0    60   ~ 0
DAC_BIP_NX
Wire Wire Line
	3225 7600 3025 7600
Text Label 3025 7600 2    60   ~ 0
GND
Wire Wire Line
	4225 7600 4425 7600
Text Label 4425 7600 0    60   ~ 0
AGND
Wire Wire Line
	3225 7500 3025 7500
Text Label 3025 7500 2    60   ~ 0
AGND
Wire Wire Line
	4225 7500 4425 7500
Text Label 4425 7500 0    60   ~ 0
DAC_BIP
$Comp
L C C?
U 1 1 57364846
P 1675 5600
F 0 "C?" H 1675 5700 40  0000 L CNN
F 1 "10nF" H 1681 5515 40  0000 L CNN
F 2 "~" H 1713 5450 30  0000 C CNN
F 3 "~" H 1675 5600 60  0000 C CNN
	1    1675 5600
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5736484C
P 950 5600
F 0 "C?" H 950 5700 40  0000 L CNN
F 1 "10nF" H 956 5515 40  0000 L CNN
F 2 "~" H 988 5450 30  0000 C CNN
F 3 "~" H 950 5600 60  0000 C CNN
	1    950  5600
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57364852
P 1975 5600
F 0 "C?" H 2025 5700 50  0000 L CNN
F 1 "4.7uf" H 2025 5500 50  0000 L CNN
F 2 "~" H 1975 5600 60  0000 C CNN
F 3 "~" H 1975 5600 60  0000 C CNN
	1    1975 5600
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57364858
P 1250 5600
F 0 "C?" H 1300 5700 50  0000 L CNN
F 1 "4.7uF" H 1300 5500 50  0000 L CNN
F 2 "~" H 1250 5600 60  0000 C CNN
F 3 "~" H 1250 5600 60  0000 C CNN
	1    1250 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 5800 1250 5900
Wire Wire Line
	1250 5900 950  5900
Wire Wire Line
	950  5900 950  5800
Wire Wire Line
	1100 5900 1100 6100
Connection ~ 1100 5900
Wire Wire Line
	1250 5400 1250 5300
Wire Wire Line
	1250 5300 950  5300
Wire Wire Line
	950  5300 950  5400
Wire Wire Line
	1100 5300 1100 5100
Connection ~ 1100 5300
Text Label 1100 5100 1    60   ~ 0
AGND
Text Label 1100 6100 3    60   ~ 0
-15V
Wire Wire Line
	1675 5400 1675 5300
Wire Wire Line
	1675 5300 1975 5300
Wire Wire Line
	1975 5300 1975 5400
Wire Wire Line
	1825 5300 1825 5100
Connection ~ 1825 5300
Wire Wire Line
	1675 5800 1675 5900
Wire Wire Line
	1675 5900 1975 5900
Wire Wire Line
	1975 5900 1975 5800
Wire Wire Line
	1825 5900 1825 6100
Connection ~ 1825 5900
Text Label 1825 6100 3    60   ~ 0
AGND
Text Label 1825 5100 1    60   ~ 0
+15V
Text Notes 925  6700 0    60   ~ 0
Scale bipolar DAC (DAC_BIP) by gain N=1,2,5, or 10 to get DAC_BIP_NX. 
Text Notes 925  6850 0    60   ~ 0
Gain is selected using digital outputs DAC_GAIN_A0 AND DAC_GAIN_A1.
$Comp
L LT1995 U?
U 1 1 57366B11
P 3650 5600
F 0 "U?" H 3650 5950 60  0000 C CNN
F 1 "LT1995" H 3650 5250 60  0000 C CNN
F 2 "~" H 3500 5600 60  0000 C CNN
F 3 "~" H 3500 5600 60  0000 C CNN
	1    3650 5600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2800 5700 3200 5700
Wire Wire Line
	4100 5700 4500 5700
Text Label 2800 5700 2    60   ~ 0
-12V
Text Label 4500 5700 0    60   ~ 0
+12V
Wire Wire Line
	2800 5800 3200 5800
Text Label 2800 5800 2    60   ~ 0
AGND
Wire Wire Line
	3200 5500 3100 5500
Wire Wire Line
	3100 5500 3100 5800
Connection ~ 3100 5800
Wire Wire Line
	3200 5600 3000 5600
Wire Wire Line
	3000 5600 3000 5400
Wire Wire Line
	2800 5400 3200 5400
Connection ~ 3000 5400
Text Label 2800 5400 2    60   ~ 0
DAC_UNI
Wire Wire Line
	4100 5600 4300 5600
Wire Wire Line
	4300 5600 4300 5400
Wire Wire Line
	4100 5400 4500 5400
Wire Wire Line
	4100 5800 4500 5800
Wire Wire Line
	4100 5500 4200 5500
Wire Wire Line
	4200 5500 4200 5800
Connection ~ 4200 5800
Connection ~ 4300 5400
Text Label 4500 5800 0    60   ~ 0
DAC_BIP
Text Label 4500 5400 0    60   ~ 0
REF_0V6
$Comp
L C C?
U 1 1 57367149
P 1750 7675
F 0 "C?" H 1750 7775 40  0000 L CNN
F 1 "0.1uF" H 1756 7590 40  0000 L CNN
F 2 "~" H 1788 7525 30  0000 C CNN
F 3 "~" H 1750 7675 60  0000 C CNN
	1    1750 7675
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5736714F
P 1025 7675
F 0 "C?" H 1025 7775 40  0000 L CNN
F 1 "0.1uF" H 1031 7590 40  0000 L CNN
F 2 "~" H 1063 7525 30  0000 C CNN
F 3 "~" H 1025 7675 60  0000 C CNN
	1    1025 7675
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57367155
P 2050 7675
F 0 "C?" H 2100 7775 50  0000 L CNN
F 1 "10uF" H 2100 7575 50  0000 L CNN
F 2 "~" H 2050 7675 60  0000 C CNN
F 3 "~" H 2050 7675 60  0000 C CNN
	1    2050 7675
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 5736715B
P 1325 7675
F 0 "C?" H 1375 7775 50  0000 L CNN
F 1 "10uF" H 1375 7575 50  0000 L CNN
F 2 "~" H 1325 7675 60  0000 C CNN
F 3 "~" H 1325 7675 60  0000 C CNN
	1    1325 7675
	1    0    0    -1  
$EndComp
Wire Wire Line
	1325 7875 1325 7975
Wire Wire Line
	1325 7975 1025 7975
Wire Wire Line
	1025 7975 1025 7875
Wire Wire Line
	1175 7975 1175 8175
Connection ~ 1175 7975
Wire Wire Line
	1325 7475 1325 7375
Wire Wire Line
	1325 7375 1025 7375
Wire Wire Line
	1025 7375 1025 7475
Wire Wire Line
	1175 7375 1175 7175
Connection ~ 1175 7375
Text Label 1175 7175 1    60   ~ 0
AGND
Text Label 1175 8175 3    60   ~ 0
-15V
Wire Wire Line
	1750 7475 1750 7375
Wire Wire Line
	1750 7375 2050 7375
Wire Wire Line
	2050 7375 2050 7475
Wire Wire Line
	1900 7375 1900 7175
Connection ~ 1900 7375
Wire Wire Line
	1750 7875 1750 7975
Wire Wire Line
	1750 7975 2050 7975
Wire Wire Line
	2050 7975 2050 7875
Wire Wire Line
	1900 7975 1900 8175
Connection ~ 1900 7975
Text Label 1900 8175 3    60   ~ 0
AGND
Text Label 1900 7175 1    60   ~ 0
+15V
Text Notes 3450 4850 0    60   ~ 0
Gain=1.67
$Comp
L MEA1D05XXSC U?
U 1 1 573678C5
P 5800 9525
F 0 "U?" H 5800 9975 60  0000 C CNN
F 1 "MEA1D05XXSC" H 5800 9075 60  0000 C CNN
F 2 "~" H 5700 9425 60  0000 C CNN
F 3 "~" H 5700 9425 60  0000 C CNN
	1    5800 9525
	1    0    0    -1  
$EndComp
Wire Wire Line
	6200 9375 6300 9375
Wire Wire Line
	6300 9375 6300 9675
Wire Wire Line
	6200 9675 6500 9675
Connection ~ 6300 9675
Text Label 6500 9675 0    60   ~ 0
GND
Wire Wire Line
	6200 9575 6500 9575
Wire Wire Line
	6200 9775 6500 9775
NoConn ~ 6200 9475
Wire Wire Line
	6200 9275 6500 9275
Text Label 6500 9575 0    60   ~ 0
-15V
Text Label 6500 9775 0    60   ~ 0
+15V
Wire Wire Line
	1850 3725 1650 3725
Text Label 1650 3725 2    60   ~ 0
5V
Text Label 6500 9275 0    60   ~ 0
5V
Text Notes 5350 8800 0    60   ~ 0
+/- 15V Supply for OPAMPs
$EndSCHEMATC

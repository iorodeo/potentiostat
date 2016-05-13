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
LIBS:potentiostat-cache
EELAYER 27 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date "13 may 2016"
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
P 2675 1900
F 0 "U?" H 2675 3250 60  0000 C CNN
F 1 "TEENSY3.1" H 2675 250 60  0000 C CNN
F 2 "~" H 2375 2100 60  0000 C CNN
F 3 "~" H 2375 2100 60  0000 C CNN
	1    2675 1900
	1    0    0    -1  
$EndComp
$Comp
L OP07 U?
U 1 1 5733FC65
P 4675 4950
F 0 "U?" H 4675 5300 60  0000 C CNN
F 1 "OP07" H 4675 4700 60  0000 C CNN
F 2 "~" H 4705 4950 60  0000 C CNN
F 3 "~" H 4705 4950 60  0000 C CNN
	1    4675 4950
	1    0    0    -1  
$EndComp
$Comp
L OP07 U?
U 1 1 5733FC74
P 8750 1750
F 0 "U?" H 8750 2100 60  0000 C CNN
F 1 "OP07" H 8750 1500 60  0000 C CNN
F 2 "~" H 8780 1750 60  0000 C CNN
F 3 "~" H 8780 1750 60  0000 C CNN
	1    8750 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	3675 700  3875 700 
Text Label 3875 700  0    60   ~ 0
DAC_UNI
Wire Wire Line
	1625 3300 1425 3300
Text Label 1425 3300 2    60   ~ 0
AGND
$Comp
L ZXRE060 U?
U 1 1 57352FD2
P 9400 6175
F 0 "U?" H 9400 5925 60  0000 C CNN
F 1 "ZXRE060" H 9400 6425 60  0000 C CNN
F 2 "~" H 9400 6175 60  0000 C CNN
F 3 "~" H 9400 6175 60  0000 C CNN
	1    9400 6175
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 57352FF0
P 8700 6425
F 0 "C?" H 8700 6525 40  0000 L CNN
F 1 "0.1uF" H 8706 6340 40  0000 L CNN
F 2 "~" H 8738 6275 30  0000 C CNN
F 3 "~" H 8700 6425 60  0000 C CNN
	1    8700 6425
	1    0    0    -1  
$EndComp
$Comp
L R R?
U 1 1 57352FFF
P 9450 6725
F 0 "R?" V 9530 6725 40  0000 C CNN
F 1 "1k" V 9457 6726 40  0000 C CNN
F 2 "~" V 9380 6725 30  0000 C CNN
F 3 "~" H 9450 6725 30  0000 C CNN
	1    9450 6725
	0    -1   -1   0   
$EndComp
$Comp
L C C?
U 1 1 57353049
P 8450 6425
F 0 "C?" H 8450 6525 40  0000 L CNN
F 1 "1uF" H 8456 6340 40  0000 L CNN
F 2 "~" H 8488 6275 30  0000 C CNN
F 3 "~" H 8450 6425 60  0000 C CNN
	1    8450 6425
	1    0    0    -1  
$EndComp
Wire Wire Line
	8450 6225 8450 6175
Wire Wire Line
	8450 6625 8450 6875
Text Label 8200 6725 2    60   ~ 0
3V3
Wire Wire Line
	3675 1000 3875 1000
Text Label 3875 1000 0    60   ~ 0
3V3
Wire Wire Line
	8200 6175 8950 6175
Connection ~ 8450 6175
Text Label 8200 6175 2    60   ~ 0
AGND
Wire Wire Line
	9850 6075 10300 6075
Wire Wire Line
	10050 6075 10050 6875
Wire Wire Line
	9850 6275 10050 6275
Connection ~ 8700 6175
Wire Wire Line
	8700 6625 8700 6725
Wire Wire Line
	8200 6725 9200 6725
Wire Wire Line
	8900 6275 8900 6725
Wire Wire Line
	8900 6275 8950 6275
Wire Wire Line
	8700 6225 8700 6175
Wire Wire Line
	8850 6175 8850 6075
Wire Wire Line
	8850 6075 8950 6075
Connection ~ 8850 6175
Connection ~ 10050 6275
Wire Wire Line
	10050 6725 9700 6725
Wire Wire Line
	10050 6875 8450 6875
Connection ~ 10050 6725
Connection ~ 8700 6725
Connection ~ 8900 6725
Connection ~ 10050 6075
Text Label 10300 6075 0    60   ~ 0
REF_0V6
Text Notes 7550 5675 0    60   ~ 0
Voltage Reference, 0.6V, Tol. 0.5%. Used in when shifting DAC_UNI to DAC_BIP.
$Comp
L R R?
U 1 1 573533E5
P 4675 4350
F 0 "R?" V 4755 4350 40  0000 C CNN
F 1 "R" V 4682 4351 40  0000 C CNN
F 2 "~" V 4605 4350 30  0000 C CNN
F 3 "~" H 4675 4350 30  0000 C CNN
	1    4675 4350
	0    -1   -1   0   
$EndComp
Wire Wire Line
	3675 4350 4425 4350
Wire Wire Line
	3675 4350 3675 4850
Wire Wire Line
	3575 4850 4175 4850
NoConn ~ 4175 4750
NoConn ~ 5175 4750
NoConn ~ 5175 5050
$Comp
L R R?
U 1 1 5735349F
P 3325 4850
F 0 "R?" V 3405 4850 40  0000 C CNN
F 1 "R" V 3332 4851 40  0000 C CNN
F 2 "~" V 3255 4850 30  0000 C CNN
F 3 "~" H 3325 4850 30  0000 C CNN
	1    3325 4850
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 573534AE
P 3325 5100
F 0 "R?" V 3405 5100 40  0000 C CNN
F 1 "R" V 3332 5101 40  0000 C CNN
F 2 "~" V 3255 5100 30  0000 C CNN
F 3 "~" H 3325 5100 30  0000 C CNN
	1    3325 5100
	0    -1   -1   0   
$EndComp
$Comp
L R R?
U 1 1 573534BD
P 3325 5350
F 0 "R?" V 3405 5350 40  0000 C CNN
F 1 "R" V 3332 5351 40  0000 C CNN
F 2 "~" V 3255 5350 30  0000 C CNN
F 3 "~" H 3325 5350 30  0000 C CNN
	1    3325 5350
	0    -1   -1   0   
$EndComp
Connection ~ 3675 4850
Wire Wire Line
	3075 4850 2825 4850
Text Label 2825 4850 2    60   ~ 0
REF_0V6
Wire Wire Line
	3675 4950 4175 4950
Wire Wire Line
	3675 4950 3675 5350
Wire Wire Line
	3675 5100 3575 5100
Wire Wire Line
	3975 5050 4175 5050
Wire Wire Line
	5175 4850 5375 4850
Text Label 3975 5050 2    60   ~ 0
-12V
Text Label 5375 4850 0    60   ~ 0
+12V
Wire Wire Line
	3675 5350 3575 5350
Connection ~ 3675 5100
Wire Wire Line
	3075 5100 2825 5100
Wire Wire Line
	3075 5350 2825 5350
Text Label 2825 5350 2    60   ~ 0
AGND
Text Label 2825 5100 2    60   ~ 0
DAC_UNI
Wire Wire Line
	5625 4350 5625 4950
Wire Wire Line
	5175 4950 5900 4950
Connection ~ 5625 4950
Wire Wire Line
	4925 4350 5625 4350
Text Notes 850  4050 0    60   ~ 0
Shifts and scales unipolar DAC (DAC_UNI) from [0V,1.2V] range to bipolar DAC (DAC_BIP) in [-1V,1V]  range. \n 
$Comp
L AD8250 U?
U 1 1 573637D1
P 3725 6950
F 0 "U?" H 3725 7300 60  0000 C CNN
F 1 "AD8250" H 3725 6550 60  0000 C CNN
F 2 "~" H 3575 6950 60  0000 C CNN
F 3 "~" H 3575 6950 60  0000 C CNN
	1    3725 6950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1625 800  1425 800 
Wire Wire Line
	1625 900  1425 900 
Text Label 1425 800  2    60   ~ 0
DAC_GAIN_A0
Text Label 1425 900  2    60   ~ 0
DAC_GAIN_A1
Wire Wire Line
	3225 7050 3025 7050
Wire Wire Line
	3225 7150 3025 7150
Text Label 3025 7050 2    60   ~ 0
DAC_GAIN_A0
Text Label 3025 7150 2    60   ~ 0
DAC_GAIN_A1
Wire Wire Line
	3225 6950 3025 6950
Wire Wire Line
	4225 6950 4425 6950
Text Label 3025 6950 2    60   ~ 0
-12V
Text Label 4425 6950 0    60   ~ 0
+12V
$Comp
L C C?
U 1 1 57363E91
P 2125 7000
F 0 "C?" H 2125 7100 40  0000 L CNN
F 1 "C" H 2131 6915 40  0000 L CNN
F 2 "~" H 2163 6850 30  0000 C CNN
F 3 "~" H 2125 7000 60  0000 C CNN
	1    2125 7000
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 57363EA0
P 1125 7000
F 0 "C?" H 1125 7100 40  0000 L CNN
F 1 "C" H 1131 6915 40  0000 L CNN
F 2 "~" H 1163 6850 30  0000 C CNN
F 3 "~" H 1125 7000 60  0000 C CNN
	1    1125 7000
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57363EAF
P 1825 7000
F 0 "C?" H 1875 7100 50  0000 L CNN
F 1 "CP1" H 1875 6900 50  0000 L CNN
F 2 "~" H 1825 7000 60  0000 C CNN
F 3 "~" H 1825 7000 60  0000 C CNN
	1    1825 7000
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57363EBE
P 1425 7000
F 0 "C?" H 1475 7100 50  0000 L CNN
F 1 "10uF" H 1475 6900 50  0000 L CNN
F 2 "~" H 1425 7000 60  0000 C CNN
F 3 "~" H 1425 7000 60  0000 C CNN
	1    1425 7000
	1    0    0    -1  
$EndComp
Wire Wire Line
	1425 7200 1425 7300
Wire Wire Line
	1425 7300 1125 7300
Wire Wire Line
	1125 7300 1125 7200
Wire Wire Line
	1275 7300 1275 7500
Connection ~ 1275 7300
Wire Wire Line
	1425 6800 1425 6700
Wire Wire Line
	1425 6700 1125 6700
Wire Wire Line
	1125 6700 1125 6800
Wire Wire Line
	1275 6700 1275 6500
Connection ~ 1275 6700
Text Label 1275 6500 1    60   ~ 0
AGND
Text Label 1275 7500 3    60   ~ 0
-12V
Wire Wire Line
	1825 6800 1825 6700
Wire Wire Line
	1825 6700 2125 6700
Wire Wire Line
	2125 6700 2125 6800
Wire Wire Line
	1975 6700 1975 6500
Connection ~ 1975 6700
Wire Wire Line
	1825 7200 1825 7300
Wire Wire Line
	1825 7300 2125 7300
Wire Wire Line
	2125 7300 2125 7200
Wire Wire Line
	1975 7300 1975 7500
Connection ~ 1975 7300
Text Label 1975 7500 3    60   ~ 0
AGND
Text Label 1975 6500 1    60   ~ 0
+12V
Wire Wire Line
	3675 900  3875 900 
Text Label 3875 900  0    60   ~ 0
GND
Text Label 5900 4950 0    60   ~ 0
DAC_BIP
Wire Wire Line
	4225 7150 4425 7150
Text Label 4425 7150 0    60   ~ 0
-12V
Wire Wire Line
	4225 7050 4425 7050
Text Label 4425 7050 0    60   ~ 0
DAC_BIP_NX
Wire Wire Line
	3225 6850 3025 6850
Text Label 3025 6850 2    60   ~ 0
GND
Wire Wire Line
	4225 6850 4425 6850
Text Label 4425 6850 0    60   ~ 0
AGND
Wire Wire Line
	3225 6750 3025 6750
Text Label 3025 6750 2    60   ~ 0
AGND
Wire Wire Line
	4225 6750 4425 6750
Text Label 4425 6750 0    60   ~ 0
DAC_BIP
$Comp
L C C?
U 1 1 57364846
P 1975 4950
F 0 "C?" H 1975 5050 40  0000 L CNN
F 1 "C" H 1981 4865 40  0000 L CNN
F 2 "~" H 2013 4800 30  0000 C CNN
F 3 "~" H 1975 4950 60  0000 C CNN
	1    1975 4950
	1    0    0    -1  
$EndComp
$Comp
L C C?
U 1 1 5736484C
P 975 4950
F 0 "C?" H 975 5050 40  0000 L CNN
F 1 "C" H 981 4865 40  0000 L CNN
F 2 "~" H 1013 4800 30  0000 C CNN
F 3 "~" H 975 4950 60  0000 C CNN
	1    975  4950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57364852
P 1675 4950
F 0 "C?" H 1725 5050 50  0000 L CNN
F 1 "CP1" H 1725 4850 50  0000 L CNN
F 2 "~" H 1675 4950 60  0000 C CNN
F 3 "~" H 1675 4950 60  0000 C CNN
	1    1675 4950
	1    0    0    -1  
$EndComp
$Comp
L CP1 C?
U 1 1 57364858
P 1275 4950
F 0 "C?" H 1325 5050 50  0000 L CNN
F 1 "10uF" H 1325 4850 50  0000 L CNN
F 2 "~" H 1275 4950 60  0000 C CNN
F 3 "~" H 1275 4950 60  0000 C CNN
	1    1275 4950
	1    0    0    -1  
$EndComp
Wire Wire Line
	1275 5150 1275 5250
Wire Wire Line
	1275 5250 975  5250
Wire Wire Line
	975  5250 975  5150
Wire Wire Line
	1125 5250 1125 5450
Connection ~ 1125 5250
Wire Wire Line
	1275 4750 1275 4650
Wire Wire Line
	1275 4650 975  4650
Wire Wire Line
	975  4650 975  4750
Wire Wire Line
	1125 4650 1125 4450
Connection ~ 1125 4650
Text Label 1125 4450 1    60   ~ 0
AGND
Text Label 1125 5450 3    60   ~ 0
-12V
Wire Wire Line
	1675 4750 1675 4650
Wire Wire Line
	1675 4650 1975 4650
Wire Wire Line
	1975 4650 1975 4750
Wire Wire Line
	1825 4650 1825 4450
Connection ~ 1825 4650
Wire Wire Line
	1675 5150 1675 5250
Wire Wire Line
	1675 5250 1975 5250
Wire Wire Line
	1975 5250 1975 5150
Wire Wire Line
	1825 5250 1825 5450
Connection ~ 1825 5250
Text Label 1825 5450 3    60   ~ 0
AGND
Text Label 1825 4450 1    60   ~ 0
+12V
Text Notes 925  5950 0    60   ~ 0
Scale bipolar DAC (DAC_BIP) by gain N=1,2,5, or 10 to get DAC_BIP_NX. 
Text Notes 925  6100 0    60   ~ 0
Gain is selected using digital outputs DAC_GAIN_A0 AND DAC_GAIN_A1.
Text Notes 900  3875 0    60   ~ 0
Maybe change this to the LT1995?  can get gain of 1.67 no need to bias resistors, etc.
$EndSCHEMATC

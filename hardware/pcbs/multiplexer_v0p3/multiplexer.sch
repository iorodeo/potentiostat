EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr User 12000 12000
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
L Connector_Generic:Conn_01x03 K1
U 1 1 5B4BC53E
P 1850 1150
F 0 "K1" V 1800 1350 50  0000 C CNN
F 1 "CONN_3" V 1950 1150 40  0000 C CNN
F 2 "" H 1850 1150 60  0000 C CNN
F 3 "" H 1850 1150 60  0000 C CNN
	1    1850 1150
	1    0    0    -1  
$EndComp
Text Label 1400 1050 2    60   ~ 0
CTR
Text Label 1400 1250 2    60   ~ 0
WRK
Text Label 1400 1150 2    60   ~ 0
REF
$Comp
L Connector_Generic:Conn_02x05_Odd_Even P2
U 1 1 5B4BC67F
P 1600 6100
F 0 "P2" H 1600 6400 60  0000 C CNN
F 1 "CONN_5X2" H 1650 5800 50  0000 C CNN
F 2 "" H 1600 6100 60  0000 C CNN
F 3 "" H 1600 6100 60  0000 C CNN
	1    1600 6100
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_02x05_Odd_Even P1
U 1 1 5B4BC7E9
P 1600 4550
F 0 "P1" H 1600 4850 60  0000 C CNN
F 1 "CONN_5X2" H 1650 4250 50  0000 C CNN
F 2 "" H 1600 4550 60  0000 C CNN
F 3 "" H 1600 4550 60  0000 C CNN
	1    1600 4550
	1    0    0    -1  
$EndComp
Text Label 1150 6000 2    60   ~ 0
D3
Text Label 1150 6100 2    60   ~ 0
D19
Text Label 1150 6200 2    60   ~ 0
D12
Text Label 1150 6300 2    60   ~ 0
D13
Text Label 2150 6000 0    60   ~ 0
D4
Text Label 2150 6100 0    60   ~ 0
D18
Text Label 2150 6200 0    60   ~ 0
D11
Text Label 2150 6300 0    60   ~ 0
D10
NoConn ~ 1400 5900
NoConn ~ 1900 5900
Text Label 2150 4350 0    60   ~ 0
GND
Text Label 1150 4450 2    60   ~ 0
D24
Text Label 1150 4550 2    60   ~ 0
D26
Text Label 1150 4650 2    60   ~ 0
D28
Text Label 1150 4750 2    60   ~ 0
D30
Text Label 2150 4450 0    60   ~ 0
D25
Text Label 2150 4550 0    60   ~ 0
D27
Text Label 2150 4650 0    60   ~ 0
D29
Text Label 2150 4750 0    60   ~ 0
D31
Wire Wire Line
	1650 1050 1400 1050
Wire Wire Line
	1650 1150 1400 1150
Wire Wire Line
	1650 1250 1400 1250
Wire Wire Line
	1900 6000 2150 6000
Wire Wire Line
	1900 6100 2150 6100
Wire Wire Line
	1900 6200 2150 6200
Wire Wire Line
	1900 6300 2150 6300
Wire Wire Line
	1400 6100 1150 6100
Wire Wire Line
	1400 6200 1150 6200
Wire Wire Line
	1400 6300 1150 6300
Wire Wire Line
	1900 4350 2150 4350
Wire Wire Line
	1900 4450 2150 4450
Wire Wire Line
	1900 4550 2150 4550
Wire Wire Line
	1900 4650 2150 4650
Wire Wire Line
	1900 4750 2150 4750
Wire Wire Line
	1400 4450 1150 4450
Wire Wire Line
	1400 4550 1150 4550
Wire Wire Line
	1400 4650 1150 4650
Wire Wire Line
	1400 4750 1150 4750
Wire Wire Line
	1400 6000 1150 6000
$Comp
L Connector_Generic:Conn_01x02 P3
U 1 1 5B4BCEAB
P 1850 2400
F 0 "P3" V 1800 2500 40  0000 C CNN
F 1 "CONN_2" V 1950 2350 40  0000 C CNN
F 2 "" H 1850 2400 60  0000 C CNN
F 3 "" H 1850 2400 60  0000 C CNN
	1    1850 2400
	1    0    0    -1  
$EndComp
$Comp
L Connector_Generic:Conn_01x02 P4
U 1 1 5B4BCEBA
P 1850 2900
F 0 "P4" V 1800 3000 40  0000 C CNN
F 1 "CONN_2" V 1950 2850 40  0000 C CNN
F 2 "" H 1850 2900 60  0000 C CNN
F 3 "" H 1850 2900 60  0000 C CNN
	1    1850 2900
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2450 1200 2450
Wire Wire Line
	1400 2950 1200 2950
Text Label 1200 2450 2    60   ~ 0
+15V
Text Label 1200 2950 2    60   ~ 0
-15V
$Comp
L Device:C C1
U 1 1 5B4BD185
P 3400 2300
F 0 "C1" H 3400 2400 40  0000 L CNN
F 1 "0.1uF" H 3406 2215 40  0000 L CNN
F 2 "~" H 3438 2150 30  0000 C CNN
F 3 "~" H 3400 2300 60  0000 C CNN
	1    3400 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5B4BD194
P 3750 2300
F 0 "C3" H 3750 2400 40  0000 L CNN
F 1 "0.1uF" H 3756 2215 40  0000 L CNN
F 2 "~" H 3788 2150 30  0000 C CNN
F 3 "~" H 3750 2300 60  0000 C CNN
	1    3750 2300
	1    0    0    -1  
$EndComp
Text Label 3400 1850 1    60   ~ 0
GND
Text Label 3400 2750 3    60   ~ 0
-15V
Text Label 3750 1850 1    60   ~ 0
+15V
Text Label 3750 2750 3    60   ~ 0
GND
$Comp
L Device:C C2
U 1 1 5B4BD3A9
P 3400 6700
F 0 "C2" H 3400 6800 40  0000 L CNN
F 1 "0.1uF" H 3406 6615 40  0000 L CNN
F 2 "~" H 3438 6550 30  0000 C CNN
F 3 "~" H 3400 6700 60  0000 C CNN
	1    3400 6700
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5B4BD3AF
P 3750 6700
F 0 "C4" H 3750 6800 40  0000 L CNN
F 1 "0.1uF" H 3756 6615 40  0000 L CNN
F 2 "~" H 3788 6550 30  0000 C CNN
F 3 "~" H 3750 6700 60  0000 C CNN
	1    3750 6700
	1    0    0    -1  
$EndComp
Text Label 3400 6250 1    60   ~ 0
GND
Text Label 3400 7150 3    60   ~ 0
-15V
Text Label 3750 6250 1    60   ~ 0
+15V
Text Label 3750 7150 3    60   ~ 0
GND
$Comp
L Device:C C5
U 1 1 5B4BD3BD
P 7300 2450
F 0 "C5" H 7300 2550 40  0000 L CNN
F 1 "0.1uF" H 7306 2365 40  0000 L CNN
F 2 "~" H 7338 2300 30  0000 C CNN
F 3 "~" H 7300 2450 60  0000 C CNN
	1    7300 2450
	1    0    0    -1  
$EndComp
$Comp
L Device:C C7
U 1 1 5B4BD3C3
P 7650 2450
F 0 "C7" H 7650 2550 40  0000 L CNN
F 1 "0.1uF" H 7656 2365 40  0000 L CNN
F 2 "~" H 7688 2300 30  0000 C CNN
F 3 "~" H 7650 2450 60  0000 C CNN
	1    7650 2450
	1    0    0    -1  
$EndComp
Text Label 7300 2000 1    60   ~ 0
GND
Text Label 7300 2900 3    60   ~ 0
-15V
Text Label 7650 2000 1    60   ~ 0
+15V
Text Label 7650 2900 3    60   ~ 0
GND
$Comp
L Device:C C6
U 1 1 5B4BD3D1
P 7300 6650
F 0 "C6" H 7300 6750 40  0000 L CNN
F 1 "0.1uF" H 7306 6565 40  0000 L CNN
F 2 "~" H 7338 6500 30  0000 C CNN
F 3 "~" H 7300 6650 60  0000 C CNN
	1    7300 6650
	1    0    0    -1  
$EndComp
$Comp
L Device:C C8
U 1 1 5B4BD3D7
P 7650 6650
F 0 "C8" H 7650 6750 40  0000 L CNN
F 1 "0.1uF" H 7656 6565 40  0000 L CNN
F 2 "~" H 7688 6500 30  0000 C CNN
F 3 "~" H 7650 6650 60  0000 C CNN
	1    7650 6650
	1    0    0    -1  
$EndComp
Text Label 7300 6200 1    60   ~ 0
GND
Text Label 7300 7100 3    60   ~ 0
-15V
Text Label 7650 6200 1    60   ~ 0
+15V
Text Label 7650 7100 3    60   ~ 0
GND
Wire Notes Line
	5650 2900 5600 2900
Wire Wire Line
	1900 7750 2150 7750
Wire Wire Line
	1400 7850 1150 7850
Wire Wire Line
	1900 7850 2150 7850
Wire Wire Line
	1400 7950 1150 7950
Wire Wire Line
	1400 7650 1100 7650
Wire Wire Line
	2200 7650 1900 7650
Wire Wire Line
	1100 7750 1400 7750
Text Label 1100 7650 2    60   ~ 0
GND
Text Label 2200 7650 0    60   ~ 0
CTR_SW
Text Label 1100 7750 2    60   ~ 0
REF_SW
Wire Wire Line
	1900 7950 2150 7950
Wire Wire Line
	1400 8050 1150 8050
Wire Wire Line
	1900 8050 2150 8050
Text Label 2150 7750 0    60   ~ 0
WRK_1
Text Label 1150 7850 2    60   ~ 0
WRK_2
Text Label 2150 7850 0    60   ~ 0
WRK_3
Text Label 1150 7950 2    60   ~ 0
WRK_4
Text Label 2150 7950 0    60   ~ 0
WRK_5
Text Label 1150 8050 2    60   ~ 0
WRK_6
Text Label 2150 8050 0    60   ~ 0
WRK_7
Text Notes 900  1650 0    100  ~ 0
Electrode connections \nto rodeostat PCB
Text Notes 2500 3300 2    100  ~ 0
Power input for switches
Text Notes 2850 6700 2    100  ~ 0
Connections from UEXT header
Text Notes 2800 5100 2    100  ~ 0
Connections from DIO header
Text Notes 2800 8400 2    100  ~ 0
Electrode Connection Header
Text Notes 6650 9150 2    100  ~ 0
Multiplexing for working electrodes 1-4
Text Notes 10600 9300 2    100  ~ 0
Multiplexing for working electrodes 5-7 plus\nswitches for counter and reference electrodes
$Comp
L power:PWR_FLAG #FLG01
U 1 1 5B4BE4A7
P 1250 9050
F 0 "#FLG01" H 1250 9145 30  0001 C CNN
F 1 "PWR_FLAG" H 1250 9230 30  0000 C CNN
F 2 "" H 1250 9050 60  0000 C CNN
F 3 "" H 1250 9050 60  0000 C CNN
	1    1250 9050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG02
U 1 1 5B4BE4B6
P 1650 9050
F 0 "#FLG02" H 1650 9145 30  0001 C CNN
F 1 "PWR_FLAG" H 1650 9230 30  0000 C CNN
F 2 "" H 1650 9050 60  0000 C CNN
F 3 "" H 1650 9050 60  0000 C CNN
	1    1650 9050
	1    0    0    -1  
$EndComp
$Comp
L power:PWR_FLAG #FLG03
U 1 1 5B4BE4C5
P 2050 9050
F 0 "#FLG03" H 2050 9145 30  0001 C CNN
F 1 "PWR_FLAG" H 2050 9230 30  0000 C CNN
F 2 "" H 2050 9050 60  0000 C CNN
F 3 "" H 2050 9050 60  0000 C CNN
	1    2050 9050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1250 9050 1250 9250
Wire Wire Line
	1650 9050 1650 9250
Wire Wire Line
	2050 9050 2050 9250
Text Label 1250 9250 3    60   ~ 0
+15V
Text Label 1650 9250 3    60   ~ 0
-15V
Text Label 2050 9250 3    60   ~ 0
GND
$Comp
L Connector_Generic:Conn_02x05_Odd_Even P5
U 1 1 5C3E8ED4
P 1600 7850
F 0 "P5" H 1600 8150 60  0000 C CNN
F 1 "CONN_5X2" H 1650 7550 50  0000 C CNN
F 2 "" H 1600 7850 60  0000 C CNN
F 3 "" H 1600 7850 60  0000 C CNN
	1    1600 7850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 1850 3400 2150
Wire Wire Line
	3400 2450 3400 2750
Wire Wire Line
	3750 1850 3750 2150
Wire Wire Line
	3750 2450 3750 2750
Wire Wire Line
	7650 2000 7650 2300
Wire Wire Line
	7650 2600 7650 2900
Wire Wire Line
	7300 2600 7300 2900
Wire Wire Line
	7300 2000 7300 2300
Wire Wire Line
	7650 6200 7650 6500
Wire Wire Line
	7650 6800 7650 7100
Wire Wire Line
	7300 6200 7300 6500
Wire Wire Line
	7300 6800 7300 7100
Wire Wire Line
	3750 6250 3750 6550
Wire Wire Line
	3400 6250 3400 6550
Wire Wire Line
	3400 6850 3400 7150
Wire Wire Line
	3750 6850 3750 7150
Wire Wire Line
	1400 2450 1400 2400
Wire Wire Line
	1400 2400 1650 2400
Wire Wire Line
	1400 2450 1400 2500
Wire Wire Line
	1400 2500 1650 2500
Connection ~ 1400 2450
Wire Wire Line
	1400 2900 1650 2900
Wire Wire Line
	1400 2900 1400 2950
Wire Wire Line
	1400 2950 1400 3000
Wire Wire Line
	1400 3000 1650 3000
Connection ~ 1400 2950
$Comp
L Analog_Switch:DG411xY U1
U 4 1 608F2D7B
P 5550 3100
F 0 "U1" H 5550 3367 50  0000 C CNN
F 1 "DG411xY" H 5550 3276 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5550 3000 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5550 3100 50  0001 C CNN
	4    5550 3100
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U1
U 5 1 608F4754
P 5600 3850
F 0 "U1" H 5880 3896 50  0000 L CNN
F 1 "DG411xY" H 5880 3805 50  0000 L CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5600 3750 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5600 3850 50  0001 C CNN
	5    5600 3850
	0    1    1    0   
$EndComp
Text Label 5000 1150 2    60   ~ 0
WRK_1
Text Label 5000 1800 2    60   ~ 0
WRK_2
Text Label 5000 2450 2    60   ~ 0
WRK_3
Text Label 5000 3100 2    60   ~ 0
WRK_4
Wire Wire Line
	5250 1150 5000 1150
Wire Wire Line
	5250 1800 5000 1800
Wire Wire Line
	5250 2450 5000 2450
Wire Wire Line
	5250 3100 5000 3100
Wire Wire Line
	5850 1150 6000 1150
Wire Wire Line
	6000 1150 6000 1800
Wire Wire Line
	6000 1800 5850 1800
Wire Wire Line
	6000 1800 6000 2450
Wire Wire Line
	6000 2450 5850 2450
Connection ~ 6000 1800
Wire Wire Line
	6000 3100 5850 3100
Wire Wire Line
	6000 2450 6000 3100
Connection ~ 6000 2450
Text Label 5000 1400 2    60   ~ 0
D24
Text Label 5000 2050 2    60   ~ 0
D25
Text Label 5000 2700 2    60   ~ 0
D26
Text Label 5000 3350 2    60   ~ 0
D27
Wire Wire Line
	5550 1400 5550 1350
Wire Wire Line
	5000 1400 5550 1400
Wire Wire Line
	5550 2000 5550 2050
Wire Wire Line
	5550 2050 5000 2050
Wire Wire Line
	5550 2650 5550 2700
Wire Wire Line
	5550 2700 5000 2700
Wire Wire Line
	5550 3300 5550 3350
Wire Wire Line
	5550 3350 5000 3350
Wire Wire Line
	6000 1150 6300 1150
Connection ~ 6000 1150
Text Label 6300 1150 0    60   ~ 0
WRK
Wire Wire Line
	6100 3850 6300 3850
Wire Wire Line
	6100 3950 6300 3950
Wire Wire Line
	5100 3850 4900 3850
Wire Wire Line
	5100 3950 4900 3950
Wire Wire Line
	1400 4350 1150 4350
Text Label 1150 4350 2    50   ~ 0
3V3
Text Label 6300 3950 0    50   ~ 0
3V3
Text Label 6300 3850 0    50   ~ 0
+15V
Text Label 4900 3950 2    50   ~ 0
-15V
Text Label 4900 3850 2    50   ~ 0
GND
$Comp
L Analog_Switch:DG411xY U1
U 3 1 608F1098
P 5550 2450
F 0 "U1" H 5550 2717 50  0000 C CNN
F 1 "DG411xY" H 5550 2626 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5550 2350 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5550 2450 50  0001 C CNN
	3    5550 2450
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U1
U 2 1 608EF729
P 5550 1800
F 0 "U1" H 5550 2067 50  0000 C CNN
F 1 "DG411xY" H 5550 1976 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5550 1700 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5550 1800 50  0001 C CNN
	2    5550 1800
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U1
U 1 1 608EE3F4
P 5550 1150
F 0 "U1" H 5550 1417 50  0000 C CNN
F 1 "DG411xY" H 5550 1326 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5550 1050 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5550 1150 50  0001 C CNN
	1    5550 1150
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U3
U 4 1 60AEEF0A
P 9500 3150
F 0 "U3" H 9500 3417 50  0000 C CNN
F 1 "DG411xY" H 9500 3326 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9500 3050 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9500 3150 50  0001 C CNN
	4    9500 3150
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U3
U 5 1 60AEF368
P 9550 3900
F 0 "U3" H 9830 3946 50  0000 L CNN
F 1 "DG411xY" H 9830 3855 50  0000 L CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9550 3800 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9550 3900 50  0001 C CNN
	5    9550 3900
	0    1    1    0   
$EndComp
Wire Wire Line
	9200 1200 8950 1200
Wire Wire Line
	9200 1850 8950 1850
Wire Wire Line
	9200 2500 8950 2500
Wire Wire Line
	9200 3150 8950 3150
Wire Wire Line
	9950 1850 9800 1850
Wire Wire Line
	9950 1850 9950 2500
Wire Wire Line
	9950 2500 9800 2500
Wire Wire Line
	9950 3150 9800 3150
Wire Wire Line
	9950 2500 9950 3150
Connection ~ 9950 2500
Wire Wire Line
	9500 1450 9500 1400
Wire Wire Line
	8950 1450 9500 1450
Wire Wire Line
	9500 2050 9500 2100
Wire Wire Line
	9500 2100 8950 2100
Wire Wire Line
	9500 2700 9500 2750
Wire Wire Line
	9500 2750 8950 2750
Wire Wire Line
	9500 3350 9500 3400
Wire Wire Line
	9500 3400 8950 3400
Wire Wire Line
	10050 3900 10250 3900
Wire Wire Line
	10050 4000 10250 4000
Wire Wire Line
	9050 3900 8850 3900
Wire Wire Line
	9050 4000 8850 4000
Text Label 10250 4000 0    50   ~ 0
3V3
Text Label 10250 3900 0    50   ~ 0
+15V
Text Label 8850 4000 2    50   ~ 0
-15V
Text Label 8850 3900 2    50   ~ 0
GND
$Comp
L Analog_Switch:DG411xY U3
U 3 1 60AEF39A
P 9500 2500
F 0 "U3" H 9500 2767 50  0000 C CNN
F 1 "DG411xY" H 9500 2676 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9500 2400 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9500 2500 50  0001 C CNN
	3    9500 2500
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U3
U 2 1 60AEF3A4
P 9500 1850
F 0 "U3" H 9500 2117 50  0000 C CNN
F 1 "DG411xY" H 9500 2026 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9500 1750 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9500 1850 50  0001 C CNN
	2    9500 1850
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U3
U 1 1 60AEF3AE
P 9500 1200
F 0 "U3" H 9500 1467 50  0000 C CNN
F 1 "DG411xY" H 9500 1376 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9500 1100 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9500 1200 50  0001 C CNN
	1    9500 1200
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U2
U 4 1 60B0EB9F
P 5600 7300
F 0 "U2" H 5600 7567 50  0000 C CNN
F 1 "DG411xY" H 5600 7476 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5600 7200 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5600 7300 50  0001 C CNN
	4    5600 7300
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U2
U 5 1 60B0F213
P 5650 8000
F 0 "U2" H 5930 8046 50  0000 L CNN
F 1 "DG411xY" H 5930 7955 50  0000 L CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5650 7900 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5650 8000 50  0001 C CNN
	5    5650 8000
	0    1    1    0   
$EndComp
Wire Wire Line
	5300 5350 5050 5350
Wire Wire Line
	5300 6000 5050 6000
Wire Wire Line
	5300 6650 5050 6650
Wire Wire Line
	5300 7300 5050 7300
Wire Wire Line
	5900 5350 6050 5350
Wire Wire Line
	6050 5350 6050 6000
Wire Wire Line
	6050 6000 5900 6000
Wire Wire Line
	6050 6000 6050 6650
Wire Wire Line
	6050 6650 5900 6650
Connection ~ 6050 6000
Wire Wire Line
	6050 7300 5900 7300
Wire Wire Line
	6050 6650 6050 7300
Connection ~ 6050 6650
Wire Wire Line
	5600 5600 5600 5550
Wire Wire Line
	5050 5600 5600 5600
Wire Wire Line
	5600 6200 5600 6250
Wire Wire Line
	5600 6250 5050 6250
Wire Wire Line
	5600 6850 5600 6900
Wire Wire Line
	5600 6900 5050 6900
Wire Wire Line
	5600 7500 5600 7550
Wire Wire Line
	5600 7550 5050 7550
Wire Wire Line
	6050 5350 6350 5350
Connection ~ 6050 5350
Wire Wire Line
	6150 8000 6350 8000
Wire Wire Line
	6150 8100 6350 8100
Wire Wire Line
	5150 8000 4950 8000
Wire Wire Line
	5150 8100 4950 8100
Text Label 6350 8100 0    50   ~ 0
3V3
Text Label 6350 8000 0    50   ~ 0
+15V
Text Label 4950 8100 2    50   ~ 0
-15V
Text Label 4950 8000 2    50   ~ 0
GND
$Comp
L Analog_Switch:DG411xY U2
U 3 1 60B0F23C
P 5600 6650
F 0 "U2" H 5600 6917 50  0000 C CNN
F 1 "DG411xY" H 5600 6826 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5600 6550 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5600 6650 50  0001 C CNN
	3    5600 6650
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U2
U 2 1 60B0F246
P 5600 6000
F 0 "U2" H 5600 6267 50  0000 C CNN
F 1 "DG411xY" H 5600 6176 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5600 5900 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5600 6000 50  0001 C CNN
	2    5600 6000
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U2
U 1 1 60B0F250
P 5600 5350
F 0 "U2" H 5600 5617 50  0000 C CNN
F 1 "DG411xY" H 5600 5526 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 5600 5250 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 5600 5350 50  0001 C CNN
	1    5600 5350
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U4
U 4 1 60B3F3AB
P 9550 7350
F 0 "U4" H 9550 7617 50  0000 C CNN
F 1 "DG411xY" H 9550 7526 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9550 7250 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9550 7350 50  0001 C CNN
	4    9550 7350
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U4
U 5 1 60B3FABD
P 9650 8050
F 0 "U4" H 9930 8096 50  0000 L CNN
F 1 "DG411xY" H 9930 8005 50  0000 L CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9650 7950 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9650 8050 50  0001 C CNN
	5    9650 8050
	0    1    1    0   
$EndComp
Wire Wire Line
	9250 5400 9000 5400
Wire Wire Line
	9250 6050 9000 6050
Wire Wire Line
	9250 6700 9000 6700
Wire Wire Line
	9250 7350 9000 7350
Wire Wire Line
	10000 6050 9850 6050
Wire Wire Line
	10000 6050 10000 6700
Wire Wire Line
	10000 6700 9850 6700
Wire Wire Line
	10000 7350 9850 7350
Wire Wire Line
	10000 6700 10000 7350
Connection ~ 10000 6700
Wire Wire Line
	9550 5650 9550 5600
Wire Wire Line
	9000 5650 9550 5650
Wire Wire Line
	9550 6250 9550 6300
Wire Wire Line
	9550 6300 9000 6300
Wire Wire Line
	9550 6900 9550 6950
Wire Wire Line
	9550 6950 9000 6950
Wire Wire Line
	9550 7550 9550 7600
Wire Wire Line
	9550 7600 9000 7600
Wire Wire Line
	10150 8050 10350 8050
Wire Wire Line
	10150 8150 10350 8150
Wire Wire Line
	9150 8050 8950 8050
Wire Wire Line
	9150 8150 8950 8150
Text Label 10350 8150 0    50   ~ 0
3V3
Text Label 10350 8050 0    50   ~ 0
+15V
Text Label 8950 8150 2    50   ~ 0
-15V
Text Label 8950 8050 2    50   ~ 0
GND
$Comp
L Analog_Switch:DG411xY U4
U 3 1 60B3FAE6
P 9550 6700
F 0 "U4" H 9550 6967 50  0000 C CNN
F 1 "DG411xY" H 9550 6876 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9550 6600 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9550 6700 50  0001 C CNN
	3    9550 6700
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U4
U 2 1 60B3FAF0
P 9550 6050
F 0 "U4" H 9550 6317 50  0000 C CNN
F 1 "DG411xY" H 9550 6226 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9550 5950 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9550 6050 50  0001 C CNN
	2    9550 6050
	1    0    0    -1  
$EndComp
$Comp
L Analog_Switch:DG411xY U4
U 1 1 60B3FAFA
P 9550 5400
F 0 "U4" H 9550 5667 50  0000 C CNN
F 1 "DG411xY" H 9550 5576 50  0000 C CNN
F 2 "Package_SO:SOIC-16_3.9x9.9mm_P1.27mm" H 9550 5300 50  0001 C CNN
F 3 "https://datasheets.maximintegrated.com/en/ds/DG411-DG413.pdf" H 9550 5400 50  0001 C CNN
	1    9550 5400
	1    0    0    -1  
$EndComp
Wire Wire Line
	9800 1200 10250 1200
Wire Wire Line
	9950 1850 10300 1850
Connection ~ 9950 1850
Wire Wire Line
	9850 5400 10300 5400
Text Label 10250 1200 0    50   ~ 0
CTR
Text Label 10300 1850 0    50   ~ 0
WRK
Text Label 6350 5350 0    50   ~ 0
GND
Text Label 10300 5400 0    50   ~ 0
REF
Wire Wire Line
	10000 6050 10300 6050
Connection ~ 10000 6050
Text Label 10300 6050 0    50   ~ 0
GND
Text Label 8950 1200 2    60   ~ 0
CTR_SW
Text Label 8950 1850 2    60   ~ 0
WRK_5
Text Label 8950 2500 2    60   ~ 0
WRK_6
Text Label 8950 3150 2    60   ~ 0
WRK_7
Text Label 8950 1450 2    60   ~ 0
D3
Text Label 8950 2100 2    60   ~ 0
D4
Text Label 8950 2750 2    60   ~ 0
D19
Text Label 8950 3400 2    60   ~ 0
D18
Text Label 5050 5350 2    60   ~ 0
WRK_1
Text Label 5050 6000 2    60   ~ 0
WRK_2
Text Label 5050 6650 2    60   ~ 0
WRK_3
Text Label 5050 7300 2    60   ~ 0
WRK_4
Text Label 5050 5600 2    60   ~ 0
D28
Text Label 5050 6250 2    60   ~ 0
D29
Text Label 5050 6900 2    60   ~ 0
D30
Text Label 5050 7550 2    60   ~ 0
D31
Text Label 9000 6050 2    60   ~ 0
WRK_5
Text Label 9000 6700 2    60   ~ 0
WRK_6
Text Label 9000 7350 2    60   ~ 0
WRK_7
Text Label 9000 5400 2    60   ~ 0
REF_SW
Text Label 9000 5650 2    60   ~ 0
D12
Text Label 9000 6300 2    60   ~ 0
D11
Text Label 9000 6950 2    60   ~ 0
D13
Text Label 9000 7600 2    60   ~ 0
D10
$Comp
L Device:C C9
U 1 1 6131BA0A
P 4100 2300
F 0 "C9" H 4100 2400 40  0000 L CNN
F 1 "0.1uF" H 4106 2215 40  0000 L CNN
F 2 "~" H 4138 2150 30  0000 C CNN
F 3 "~" H 4100 2300 60  0000 C CNN
	1    4100 2300
	1    0    0    -1  
$EndComp
Text Label 4100 1850 1    60   ~ 0
3V3
Text Label 4100 2750 3    60   ~ 0
GND
Wire Wire Line
	4100 1850 4100 2150
Wire Wire Line
	4100 2450 4100 2750
$Comp
L Device:C C10
U 1 1 613577FD
P 4100 6700
F 0 "C10" H 4100 6800 40  0000 L CNN
F 1 "0.1uF" H 4106 6615 40  0000 L CNN
F 2 "~" H 4138 6550 30  0000 C CNN
F 3 "~" H 4100 6700 60  0000 C CNN
	1    4100 6700
	1    0    0    -1  
$EndComp
Text Label 4100 6250 1    60   ~ 0
3V3
Text Label 4100 7150 3    60   ~ 0
GND
Wire Wire Line
	4100 6250 4100 6550
Wire Wire Line
	4100 6850 4100 7150
$Comp
L Device:C C11
U 1 1 613A6030
P 8000 2450
F 0 "C11" H 8000 2550 40  0000 L CNN
F 1 "0.1uF" H 8006 2365 40  0000 L CNN
F 2 "~" H 8038 2300 30  0000 C CNN
F 3 "~" H 8000 2450 60  0000 C CNN
	1    8000 2450
	1    0    0    -1  
$EndComp
Text Label 8000 2000 1    60   ~ 0
3V3
Text Label 8000 2900 3    60   ~ 0
GND
Wire Wire Line
	8000 2000 8000 2300
Wire Wire Line
	8000 2600 8000 2900
$Comp
L Device:C C12
U 1 1 613D346A
P 8000 6650
F 0 "C12" H 8000 6750 40  0000 L CNN
F 1 "0.1uF" H 8006 6565 40  0000 L CNN
F 2 "~" H 8038 6500 30  0000 C CNN
F 3 "~" H 8000 6650 60  0000 C CNN
	1    8000 6650
	1    0    0    -1  
$EndComp
Text Label 8000 6200 1    60   ~ 0
3V3
Text Label 8000 7100 3    60   ~ 0
GND
Wire Wire Line
	8000 6200 8000 6500
Wire Wire Line
	8000 6800 8000 7100
Wire Notes Line
	3600 8950 6550 8950
Wire Notes Line
	7150 8950 10500 8950
$EndSCHEMATC

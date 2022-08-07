EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Connector_Generic:Conn_01x03 J1
U 1 1 62D5B0CA
P 2575 1675
F 0 "J1" H 2650 1675 50  0000 L CNN
F 1 "Conn_01x03" H 2655 1626 50  0001 L CNN
F 2 "GCT_BG300:BG300_03" H 2575 1675 50  0001 C CNN
F 3 "~" H 2575 1675 50  0001 C CNN
	1    2575 1675
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R1
U 1 1 62D5B80A
P 1725 1525
F 0 "R1" H 1575 1525 50  0000 L CNN
F 1 "50k" H 1775 1525 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric" H 1725 1525 50  0001 C CNN
F 3 "~" H 1725 1525 50  0001 C CNN
	1    1725 1525
	1    0    0    -1  
$EndComp
Text Label 2200 1575 0    50   ~ 0
WRK
Text Label 2200 1675 0    50   ~ 0
REF
Text Label 2200 1775 0    50   ~ 0
CTR
Wire Wire Line
	1725 1425 1725 1350
Wire Wire Line
	1725 1350 2075 1350
Wire Wire Line
	2075 1350 2075 1575
Wire Wire Line
	2075 1575 2375 1575
Wire Wire Line
	1725 1625 1725 1675
Wire Wire Line
	1725 1675 2375 1675
Wire Wire Line
	1725 1675 1725 1775
Wire Wire Line
	1725 1775 2375 1775
Connection ~ 1725 1675
Text Notes 1400 2700 0    50   ~ 0
Notes:\n\n1. SMT 3-pin connector BG300-03-A-L-A  (Mouser 640-BG300-03-A-L-A)\n\n2. Resistor YAGEO RT0603BRD0749K9L  ( JLCPCB C705780)\n
$EndSCHEMATC

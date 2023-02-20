#ifndef PS_HARDWARE_DEFS_H
#define PS_HARDWARE_DEFS_H

    #if 1 
        // Hardware version 0.2 
        // ------------------------------------------------------------------------
        #define HARDWARE_VERSION_0P2
        #define VOLTAGE_VARIANT_10V       
        #define CURRENT_VARIANT_MICRO_AMP   // select from (NANO, MICRO or MILL)
        //#define DEVBOARD_TEENSY             // select from (TEENSY or ITSY_BITSY)
        #define DEVBOARD_ITSY_BITSY            // select from (TEENSY or ITSY_BITSY)
    #else
        // Hardware version 0.1
        // ------------------------------------------------------------------------ 
        #define HARDWARE_VERSION_0P1
        #define VOLTAGE_VARIANT_AD8250      // select from (AD8250 or AD8251)
        #define CURRENT_VARIANT_MICRO_AMP   // select from (NANO, MICRO or MILL)
        #define DEVBOARD_TEENSY             // select from (TEENSY)
    #endif

    #if defined DEVBOARD_TEENSY
        #define MUX_CAPABLE 
    #endif

#endif

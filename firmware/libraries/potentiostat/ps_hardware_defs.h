#ifndef PS_HARDWARE_DEFS_H
#define PS_HARDWARE_DEFS_H

    // Select hardware version
    // ------------------------------------------------------------------------------
    #define HARDWARE_VERSION_0P2   // select from (VERSION_0P1 OR VERSION_0P2)
    #if defined(HARDWARE_VERSION_0P1) && defined(HARDWARE_VERSION_0P2)
        #error "only one hardware version can be defined"
    #endif

    // Options based on hardware version 
    #if defined HARDWARE_VERSION_0P2 
        #define VOLTAGE_VARIANT_10V          // select from (10V)   
        #define CURRENT_VARIANT_MILL10_AMP   // select from (MICRO, MILL10, MILL24)
        #define DEVBOARD_ITSY_BITSY          // select from (TEENSY or ITSY_BITSY)
    #elif defined HARDWARE_VERIONS_0P1 
        #define VOLTAGE_VARIANT_AD8250      // select from (AD8250 or AD8251)
        #define CURRENT_VARIANT_MICRO_AMP   // select from (NANO, MICRO or MILL24)
        #define DEVBOARD_TEENSY             // select from (TEENSY)
    #else
        #error "must define hardware verion"
    #endif

    #if defined DEVBOARD_TEENSY
        #define MUX_CAPABLE 
    #endif

#endif

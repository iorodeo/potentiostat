#ifndef PS_HARDWARE_VARIANT_DEFS_H
#define PS_HARDWARE_VARIANT_DEFS_H

// Hardware version (select one)
// ----------------------------------------------------
//#define HARDWARE_VERSION_0P1
#define HARDWARE_VERSION_0P2

// Voltage Hardware Variant (select one) 
// ----------------------------------------------------
#if defined HARDWARE_VERSION_0P1
    #define VOLTAGE_VARIANT_AD8250  
    //#define VOLTAGE_VARIANT_AD8251  
#elif defined HARDWARE_VERSION_0P2
    #define VOLTAGE_VARIANT_10V       
#endif

// Current Hardware Variant (select one)
// ----------------------------------------------------
#define CURRENT_VARIANT_MICRO_AMP
//#define CURRENT_VARIANT_NANO_AMP
//#define CURRENT_VARIANT_MILL_AMP

#endif

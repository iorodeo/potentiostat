#ifndef PS_HARDWARE_DEFS_H
#define PS_HARDWARE_DEFS_H
    
    // Select hardware version
    // ---------------------------------------------------------------
     #define HW0P2_ITSY_BITSY_10V_MICR0
    // #define HW0P2_ITSY_BITSY_10V_MILL10
    // #define HW0P2_TEENSY_10V_MICRO
    // #define HW0P1_TEENSY_10V_MICRO
    // #define HW0P1_TEENSY_10V_MILL24
    // #define HW0P1_TEENSY_10V_NANO 
    // #define HW0P1_TEENSY_8V_MICRO
    // ---------------------------------------------------------------

    // Set options based on hardware verion
    #if defined HW0P2_ITSY_BITSY_10V_MICR0

        #define HARDWARE_VERSION_0P2   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MICRO_AMP   
        #define DEVBOARD_ITSY_BITSY          

    #elif defined HW0P2_ITSY_BITSY_10V_MILL10 

        #define HARDWARE_VERSION_0P2   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MILL10_AMP   
        #define DEVBOARD_ITSY_BITSY          

    #elif defined HW0P2_TEENSY_10V_MICRO

        #define HARDWARE_VERSION_0P2   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MICRO_AMP   
        #define DEVBOARD_TEENSY         

    #elif defined HW0P1_TEENSY_10V_MICRO

        #define HARDWARE_VERSION_0P1   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MICRO_AMP   
        #define DEVBOARD_TEENSY         
    
    #elif defined HW0P1_TEENSY_10V_MILL24

        #define HARDWARE_VERSION_0P1   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MILL24_AMP   
        #define DEVBOARD_TEENSY         

    #elif defined HW0P1_TEENSY_10V_NANO 

        #define HARDWARE_VERSION_0P1   
        #define VOLTAGE_VARIANT_10V          
        #define CURRENT_VARIANT_MILL24_AMP   
        #define DEVBOARD_TEENSY         

    #elif defined HW0P1_TEENSY_8V_MICRO

        #define HARDWARE_VERSION_0P1   
        #define VOLTAGE_VARIANT_AD8251      
        #define CURRENT_VARIANT_MILL24_AMP   
        #define DEVBOARD_TEENSY         
    
    #else

        #error "no hardware version selected must select a hardware verion"

    #endif
    
    // Select hardware version
    // ------------------------------------------------------------------------------
    //#define HARDWARE_VERSION_0P2   // select from (VERSION_0P1 OR VERSION_0P2)
    //#if defined(HARDWARE_VERSION_0P1) && defined(HARDWARE_VERSION_0P2)
    //    #error "only one hardware version can be defined"
    //#endif

    //// Options based on hardware version 
    //#if defined HARDWARE_VERSION_0P2 
    //    #define VOLTAGE_VARIANT_10V          // select from (10V)   
    //    //#define CURRENT_VARIANT_MILL10_AMP   // select from (MICRO, MILL10, MILL24)
    //    #define CURRENT_VARIANT_MICRO_AMP    // select from (MICRO, MILL10, MILL24)
    //    #define DEVBOARD_ITSY_BITSY          // select from (TEENSY or ITSY_BITSY)
    //    //#define DEVBOARD_TEENSY             // select from (TEENSY)
    //#elif defined HARDWARE_VERIONS_0P1 
    //    #define VOLTAGE_VARIANT_AD8250      // select from (AD8250 or AD8251)
    //    #define CURRENT_VARIANT_MICRO_AMP   // select from (NANO, MICRO or MILL24)
    //    #define DEVBOARD_TEENSY             // select from (TEENSY)
    //#else
    //    #error "must define hardware verion"
    //#endif

    #if defined DEVBOARD_TEENSY
        #define MUX_CAPABLE 
    #endif

#endif

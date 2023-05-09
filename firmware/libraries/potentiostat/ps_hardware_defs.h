#ifndef PS_HARDWARE_DEFS_H
#define PS_HARDWARE_DEFS_H
    
    // Select your hardware version
    // ---------------------------------------------------------------
    #define HW0P2_ITSY_BITSY_10V_MICR0
    //#define HW0P2_ITSY_BITSY_10V_MILL10
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

    
    #if defined DEVBOARD_TEENSY
        #define MUX_CAPABLE 
    #endif

#endif

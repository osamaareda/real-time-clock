/**
  Generated Pin Manager File
*/

#include "pin_manager.h"

void PIN_MANAGER_Initialize(void)
{
    /**
    LATx registers
    */
    LATE = 0x00;
    LATD = 0x00;
    LATA = 0x00;
    LATB = 0x00;
    LATC = 0x00;

    /**
    TRISx registers
    */
    TRISE = 0x07;
    TRISA = 0xFF;
    TRISB = 0xFF;
    TRISC = 0xFF;
    TRISD = 0xFF; 
}
  
void PIN_MANAGER_IOC(void)
{   
	// Clear global Interrupt-On-Change flag
    INTCONbits.RBIF = 0;
}

/**
 End of File
*/
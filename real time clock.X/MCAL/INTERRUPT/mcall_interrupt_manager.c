/* 
 * File:   mcall_interrupt_manager.c
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:14 AM
 */

#include"mcall_interrupt_manager.h"
static volatile uint8 RB4_Flag = 1, RB5_Flag = 1, RB6_Flag = 1, RB7_Flag = 1;
#if INTERRUPT_PRIORITY_LEVELS==ENABLE
void __interrupt() InterruptManagerHigh(void){
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    /* ============ INTx External Interrupt End ============ */
}

void __interrupt(low_priority) InterruptManagerLow(void){
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR();
    }
    /* ============ INTx External Interrupt End ============ */
    
     /* ============ PortB External Interrupt Start ============ */
    
    /* ============ PortB External Interrupt END ============ */
    
    /* ================ ADC Interrupt Start ================= */
    
    /* ================= TIMER0 Interrupt Start ================== */
}

#else
void __interrupt() InterruptManager(void){
    /* ============ INTx External Interrupt Start ============ */
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR(); /* External Interrupt 0 */
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1E) && (INTERRUPT_OCCUR == INTCON3bits.INT1F)){
        INT1_ISR(); /* External Interrupt 1 */
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR(); /* External Interrupt 2 */
    }
    /* ============ INTx External Interrupt End ============ */
    
   
}
#endif
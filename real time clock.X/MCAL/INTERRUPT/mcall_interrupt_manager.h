/* 
 * File:   mcall_interrupt_manager.h
 * Author: osama reda
 *
 * Created on October 8, 2023, 12:14 AM
 */

#ifndef MCALL_INTERRUPT_MANAGER_H
#define	MCALL_INTERRUPT_MANAGER_H

/*-----------------------includes-------------------------*/
#include"mcall_interrupt_cfg.h"

/*----------------function declaration-----------------*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);
void RB4_ISR(uint8 RB4_Source);
void RB5_ISR(uint8 RB5_Source);
void RB6_ISR(uint8 RB6_Source);
void RB7_ISR(uint8 RB7_Source);
void ADC_ISR(void);
void TMR0_ISR(void);
void TMR1_ISR(void);
void TMR2_ISR(void);
void TMR3_ISR(void);
void CCP1_ISR(void);
void CCP2_ISR(void);
void EUSART_TX_ISR(void);
void EUSART_RX_ISR(void);
//void SPI_ISR(void);
void I2C_ISR(void);
void I2C_BC_ISR(void);
#endif	/* MCALL_INTERRUPT_MANAGER_H */
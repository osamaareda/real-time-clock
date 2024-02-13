/* 
 * File:   init.h
 * Author: osama reda
 * Created on february 13, 2024, 5:32 AM
 */

#ifndef INIT_H
#define	INIT_H

/*-------------------includes---------------------*/
#include "device_config.h"
#include "../mcc_generated_files/examples/i2c_master_example.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/RealTimeClockDS1307/RealTimeClockDS1307.h"
#include "../MCAL/INTERRUPT/mcal_external_interrupt.h"

/*--------------function declaration--------------*/
void _Initialize(void);
void APP_INT0_ISR(void);
void APP_INT1_ISR(void);

/*--------------------externs---------------------*/
extern lcd_config_t lcd;
extern interrupt_INTx_t MY_INT0;
extern interrupt_INTx_t MY_INT1;
#endif	/* INIT_H */

/* 
 * File:   init.c
 * Author: osama reda
 * Created on february 13, 2024, 5:32 AM
 */
#include "init.h"
/*============================lcd configuration===========================*/
lcd_config_t lcd={.lcd_rs.port=PORTD_INDEX,.lcd_rs.pin=PIN4,
                  .lcd_en.port=PORTD_INDEX,.lcd_en.pin=PIN5,
                  .lcd_pins[0].port=PORTD_INDEX,.lcd_pins[0].pin=PIN0,
                  .lcd_pins[1].port=PORTD_INDEX,.lcd_pins[1].pin=PIN1,
                  .lcd_pins[2].port=PORTD_INDEX,.lcd_pins[2].pin=PIN2,
                  .lcd_pins[3].port=PORTD_INDEX,.lcd_pins[3].pin=PIN3};

/*============================interrupt configuration===========================*/
interrupt_INTx_t MY_INT0={
    .EXT_InterruptHandler=APP_INT0_ISR,
    .INTx_pin.port=PORTB_INDEX,
    .INTx_pin.pin=PIN0,
    .edge=RISING_EDGE,
    .source=_INT0};

interrupt_INTx_t MY_INT1={
    .EXT_InterruptHandler=APP_INT1_ISR,
    .INTx_pin.port=PORTB_INDEX,
    .INTx_pin.pin=PIN1,
    .edge=RISING_EDGE,
    .source=_INT1};


void _Initialize(void){
    
    I2C_Initialize();
    lcd_init(&lcd);
    interrupt_INTx_init(&MY_INT0);
    interrupt_INTx_init(&MY_INT1);
}



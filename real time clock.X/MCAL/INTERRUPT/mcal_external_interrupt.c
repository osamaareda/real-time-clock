/* 
 * File:   mcal_external_interrupt.c
 * Author: osama reda
 * Created on february 13, 2024, 5:32 AM
 */

#include"mcal_external_interrupt.h"
#if EXTERNAL_INTERRUPT_INTx_FEATURE==ENABLE
/* Pointer to function to hold the callbacks func for INTx */
static void (*INT0_InterruptHandler)(void)=NULL;
static void (*INT1_InterruptHandler)(void)=NULL;
static void (*INT2_InterruptHandler)(void)=NULL;

/* helper function to initialize INTx interrupt */
//to initialize callback func
static Std_ReturnType INT0_set_InterruptHandler(void (*InterruptHandeller)(void));
static Std_ReturnType INT1_set_InterruptHandler(void (*InterruptHandeller)(void));
static Std_ReturnType INT2_set_InterruptHandler(void (*InterruptHandeller)(void));
static Std_ReturnType INTx_select_InterruptHandler( interrupt_INTx_t *_interrupt);
//to enable, disable, clear flag and set(priority,edge,pin)
static Std_ReturnType interrupt_INTx_enable( interrupt_INTx_t *_interrupt);
static Std_ReturnType interrupt_INTx_disable( interrupt_INTx_t *_interrupt);
static Std_ReturnType interrupt_INTx_clear_flag( interrupt_INTx_t *_interrupt);
static Std_ReturnType interrupt_INTx_priority_init( interrupt_INTx_t *_interrupt);
static Std_ReturnType interrupt_INTx_edge_init( interrupt_INTx_t *_interrupt);
static Std_ReturnType interrupt_INTx_pin_init( interrupt_INTx_t *_interrupt);
#endif

#if EXTERNAL_INTERRUPT_OnChange_FEATURE ==ENABLE
/* Pointer to function to hold the callbacks func for RBx */
static void (*RB4_InterruptHandler_high)(void)=NULL;
static void (*RB4_InterruptHandler_low)(void)=NULL;
static void (*RB5_InterruptHandler_high)(void)=NULL;
static void (*RB5_InterruptHandler_low)(void)=NULL;
static void (*RB6_InterruptHandler_high)(void)=NULL;
static void (*RB6_InterruptHandler_low)(void)=NULL;
static void (*RB7_InterruptHandler_high)(void)=NULL;
static void (*RB7_InterruptHandler_low)(void)=NULL;

/* helper function to initialize RBx interrupt */
//to initialize callback func
static Std_ReturnType RBx_select_InterruptHandler( interrupt_RBx_t *_interrupt);
//to set priority and pin
static Std_ReturnType interrupt_RBx_priority_init( interrupt_RBx_t *_interrupt);
static Std_ReturnType interrupt_RBx_pin_init( interrupt_RBx_t *_interrupt);
#endif

#if EXTERNAL_INTERRUPT_INTx_FEATURE==ENABLE
/**
 * @brief  :Initialize INTx external interrupt
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType interrupt_INTx_init( interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        
        //disable INTx interrupt
        ret=interrupt_INTx_disable(_interrupt);
        //clear flag
        ret|=interrupt_INTx_clear_flag(_interrupt);  
        //set priority levels for INTx
        #if INTERRUPT_PRIORITY_LEVELS==ENABLE
        ret|=interrupt_INTx_priority_init(_interrupt);
        #endif
        //set edge detection
        ret|=interrupt_INTx_edge_init(_interrupt);        
        //Initialize the INTx pin to be input
        ret|=interrupt_INTx_pin_init(_interrupt);     
        //Initialize the call back functions
        ret|=INTx_select_InterruptHandler(_interrupt);
        //enable INTx interrupt
        ret|=interrupt_INTx_enable(_interrupt);
        
    }
    
    return ret;
}
/**
 * External Interrupt INT0 MCAL Helper function 
 */
void INT0_ISR(void){
    //clear INT0 external interrupt flag
    EXT_INT0_InterruptFlagClear();
    //Application Callback function gets called every time this ISR executes
    if(INT0_InterruptHandler){INT0_InterruptHandler();}
}
/**
 * External Interrupt INT1 MCAL Helper function 
 */
void INT1_ISR(void){
    //clear INT1 external interrupt flag
    EXT_INT1_InterruptFlagClear();
    //Application Callback function gets called every time this ISR executes
    if(INT1_InterruptHandler){INT1_InterruptHandler();}
}
/**
 * External Interrupt INT2 MCAL Helper function 
 */
void INT2_ISR(void){
    //clear INT2 external interrupt flag
    EXT_INT2_InterruptFlagClear();
    //Application Callback function gets called every time this ISR executes
    if(INT2_InterruptHandler){INT2_InterruptHandler();}
}
/**
 * @brief  : deinitialize INTx external interrupt
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
Std_ReturnType interrupt_INTx_deInit(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        ret=interrupt_INTx_disable(_interrupt);
    }
    
    return ret;
}
/**
 * @brief  : enable INTx external interrupt
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_enable(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            case _INT0 :
                #if INTERRUPT_PRIORITY_LEVELS==ENABLE
                INTERRUPT_PriorityLevelsEnable();
                INTERRUPT_GlobalInterruptHighEnable();
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                
                #endif
                EXT_INT0_InterruptEnable();
                ret=E_OK;
                break;
            case _INT1 :
                #if INTERRUPT_PRIORITY_LEVELS==ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(HIGH_PRIORITY==_interrupt->priority){INTERRUPT_GlobalInterruptHighEnable();}
                else if (LOW_PRIORITY==_interrupt->priority){INTERRUPT_GlobalInterruptLowEnable();}
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT1_InterruptEnable();
                ret=E_OK;
                break;
            case _INT2 :
                #if INTERRUPT_PRIORITY_LEVELS==ENABLE
                INTERRUPT_PriorityLevelsEnable();
                if(HIGH_PRIORITY==_interrupt->priority){INTERRUPT_GlobalInterruptHighEnable();}
                else if (LOW_PRIORITY==_interrupt->priority){INTERRUPT_GlobalInterruptLowEnable();}
                #else
                INTERRUPT_GlobalInterruptEnable();
                INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_InterruptEnable();
                ret=E_OK;
                break;
            default    :
                ret=E_NOT_OK; 
                break;
        } 
    }
    
    return ret;
}
/**
 * @brief  : disable INTx external interrupt
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_disable(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            case _INT0 :
                EXT_INT0_InterruptDisable();
                ret=E_OK;
                break;
            case _INT1 :
                EXT_INT1_InterruptDisable();
                ret=E_OK;
                break;
            case _INT2 :
                EXT_INT2_InterruptDisable();
                ret=E_OK;
                break;
            default    :
                ret=E_NOT_OK; 
                break;
        }
    }
    
    return ret;
}
/**
 * @brief  : clear INTx external interrupt flag
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_clear_flag(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            case _INT0 :
                EXT_INT0_InterruptFlagClear();
                ret=E_OK;
                break;
            case _INT1 :
                EXT_INT0_InterruptFlagClear();
                ret=E_OK;
                break;
            case _INT2 :
                EXT_INT0_InterruptFlagClear();
                ret=E_OK;
                break;
            default    :
                ret=E_NOT_OK; 
                break;
        }
    }
    
    return ret;
}
/**
 * @brief  : set priority for INTx external interrupt if priority levels are enabled
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
#if INTERRUPT_PRIORITY_LEVELS==ENABLE
static Std_ReturnType interrupt_INTx_priority_init(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            
            case _INT1 :
                if(HIGH_PRIORITY==_interrupt->priority){EXT_INT1_HighPrioritySet();}
                else if (LOW_PRIORITY==_interrupt->priority){EXT_INT1_LowPrioritySet();}
                ret=E_OK;
                break;
            case _INT2 :
                if(HIGH_PRIORITY==_interrupt->priority){EXT_INT2_HighPrioritySet();}
                else if (LOW_PRIORITY==_interrupt->priority){EXT_INT2_LowPrioritySet();}
                ret=E_OK;
                break;
            default    :
                ret=E_NOT_OK; 
                break;
        }
    }
    
    return ret;
}
#endif
/**
 * @brief  : initialize INTx external interrupt edge either rising or falling
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_edge_init(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            case _INT0 :
                if(RISING_EDGE==_interrupt->edge){ EXT_INT0_RisingEdgeSet();}
                else if (FALLING_EDGE==_interrupt->edge){EXT_INT0_FallingEdgeSet();}
                ret=E_OK;
                break;
            case _INT1 :
                if(RISING_EDGE==_interrupt->edge){EXT_INT1_RisingEdgeSet();}
                else if (FALLING_EDGE==_interrupt->edge){EXT_INT1_FallingEdgeSet();}
                ret=E_OK;
                break;
            case _INT2 :
                if(RISING_EDGE==_interrupt->edge){EXT_INT2_RisingEdgeSet();}
                else if (FALLING_EDGE==_interrupt->edge){EXT_INT2_FallingEdgeSet();}
                ret=E_OK;
                break;
            default    :
                ret=E_NOT_OK; 
                break;
        }
    }
    
    return ret;
}
/**
 * @brief  : set INTx external interrupt pin to be input
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType interrupt_INTx_pin_init(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        ret=gpio_pin_input_init(&(_interrupt->INTx_pin));
    }
    
    return ret;
}
/**
 * @brief  : link ISR_app with INTx_ISR
 * @param  : _interrupt -> pointer to (interrupt_INTx_t) structure @ref interrupt_INTx_t
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INTx_select_InterruptHandler(interrupt_INTx_t *_interrupt){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==_interrupt){
        ret=E_NOT_OK;
    }
    else{
        switch(_interrupt->source){
            case _INT0 :
                ret=INT0_set_InterruptHandler(_interrupt->EXT_InterruptHandler);
                break;
            case _INT1 :
                ret=INT1_set_InterruptHandler(_interrupt->EXT_InterruptHandler);
                break;
            case _INT2 :
                ret=INT2_set_InterruptHandler(_interrupt->EXT_InterruptHandler);
                break;
            default    : 
                ret=E_NOT_OK; 
                break;
        }
    }
    
    return ret;
}
/**
 * @brief  : set INT0 pointer to function with ISR_app address
 * @param  : InterruptHandler-> pointer to function
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT0_set_InterruptHandler(void (*InterruptHandler)(void)){
    
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT0_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    
    return ret;
}
/**
 * @brief  : set INT1 pointer to function with ISR_app address
 * @param  : InterruptHandler-> pointer to function
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT1_set_InterruptHandler(void (*InterruptHandler)(void)){
     
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT1_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    
    return ret;
}
/**
 * @brief  : set INT2 pointer to function with ISR_app address
 * @param  : InterruptHandler-> pointer to function
 * @return : Status of the function
 *          (E_OK) : The function done successfully
 *          (E_NOT_OK) : The function has issue to perform this action
 */
static Std_ReturnType INT2_set_InterruptHandler(void (*InterruptHandler)(void)){
     
    Std_ReturnType ret=E_NOT_OK;
    if(NULL==InterruptHandler){
        ret=E_NOT_OK;
    }
    else{
        INT2_InterruptHandler=InterruptHandler;
        ret=E_OK;
    }
    
    return ret;
}
#endif

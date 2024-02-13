/* 
 * File:   RealTimeClockDS1307.h
 * Author: osama reda
 * Created on february 13, 2024, 5:32 AM
 */

#ifndef REALTIMECLOCKDS1307_H
#define	REALTIMECLOCKDS1307_H

#include "../../mcc_generated_files/init.h"
#include "../../mcc_generated_files/examples/i2c_master_example.h"


typedef struct{
    uint8_t _Hours;
    uint8_t _Minutes;
    uint8_t _Seconds;
    uint8_t _Year;
    uint8_t _Month;
    uint8_t _Day;
}RealTimeClockDS1307_T;

/*--------------function declaration--------------*/
RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void);
void convert_BCD_to_int(uint8 BCD_num,uint8 *int_num);
void convert_int_to_BCD(uint8 int_num,uint8 *BCD_num);

#endif	/* REALTIMECLOCKDS1307_H */


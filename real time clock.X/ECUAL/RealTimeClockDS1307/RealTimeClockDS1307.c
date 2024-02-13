/* 
 * File:   RealTimeClockDS1307.c
 * Author: Ahmed Abd El-Ghafar
 * Created on February 18, 2023, 1:48 PM
 */

#include "RealTimeClockDS1307.h"

static RealTimeClockDS1307_T RTC1307;
RealTimeClockDS1307_T RealTimeClockDS1307_Get_Date_Time(void){
    RTC1307._Seconds = I2C_Read1ByteRegister(0xD0, 0x00);
    RTC1307._Minutes = I2C_Read1ByteRegister(0xD0, 0x01);
    RTC1307._Hours   = I2C_Read1ByteRegister(0xD0, 0x02);
    RTC1307._Day     = I2C_Read1ByteRegister(0xD0, 0x04);
    RTC1307._Month   = I2C_Read1ByteRegister(0xD0, 0x05);
    RTC1307._Year    = I2C_Read1ByteRegister(0xD0, 0x06);
    
    return RTC1307;
}

void convert_BCD_to_int(uint8 BCD_num,uint8 *int_num){
    uint8 tens,ones;
    switch(BCD_num&0x0f){
        case 0b0000: ones=0; break;
        case 0b0001: ones=1; break;
        case 0b0010: ones=2; break;
        case 0b0011: ones=3; break;
        case 0b0100: ones=4; break;
        case 0b0101: ones=5; break;
        case 0b0110: ones=6; break;
        case 0b0111: ones=7; break;
        case 0b1000: ones=8; break;
        case 0b1001: ones=9; break;  
    }
    switch(BCD_num>>4){
        case 0b0000: tens=0; break;
        case 0b0001: tens=1; break;
        case 0b0010: tens=2; break;
        case 0b0011: tens=3; break;
        case 0b0100: tens=4; break;
        case 0b0101: tens=5; break;
        case 0b0110: tens=6; break;
        case 0b0111: tens=7; break;
        case 0b1000: tens=8; break;
        case 0b1001: tens=9; break;  
    }
    *int_num=tens*10+ones;
}

void convert_int_to_BCD(uint8 int_num,uint8 *BCD_num){
    uint8 l_nipple,h_nipple;
    switch(int_num%10){
        case 0: l_nipple=0b0000; break;
        case 1: l_nipple=0b0001; break;
        case 2: l_nipple=0b0010; break;
        case 3: l_nipple=0b0011; break;
        case 4: l_nipple=0b0100; break;
        case 5: l_nipple=0b0101; break;
        case 6: l_nipple=0b0110; break;
        case 7: l_nipple=0b0111; break;
        case 8: l_nipple=0b1000; break;
        case 9: l_nipple=0b1000; break;  
    }
    switch(int_num/10){
        case 0: h_nipple=0b0000; break;
        case 1: h_nipple=0b0001; break;
        case 2: h_nipple=0b0010; break;
        case 3: h_nipple=0b0011; break;
        case 4: h_nipple=0b0100; break;
        case 5: h_nipple=0b0101; break;
        case 6: h_nipple=0b0110; break;
        case 7: h_nipple=0b0111; break;
        case 8: h_nipple=0b1000; break;
        case 9: h_nipple=0b1000; break;    
    }
    *BCD_num=(h_nipple<<4)|(l_nipple);
}
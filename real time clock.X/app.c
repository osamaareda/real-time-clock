/* 
 * File:   app.c
 * Author: osama reda
 * Created on february 13, 2024, 5:32 AM
 */
#include "app.h"

/*=============================main code===============================*/
volatile RealTimeClockDS1307_T RTC1307;
volatile uint8 option_counter=0;
volatile uint8 seconds_counter=0;
volatile uint8 minutes_counter=0;
volatile uint8 hours_counter=0;
volatile uint8 day_counter=1;
volatile uint8 month_counter=1;
volatile uint8 year_counter=1;

void APP_INT0_ISR(void){
    if(option_counter==0){
       RTC1307 = RealTimeClockDS1307_Get_Date_Time();
    }
    option_counter++;
    if(option_counter==7){
       option_counter=0;
       /*send the updated values to the RTC*/
       I2C_Write1ByteRegister(0xD0, 0x00,RTC1307._Seconds);
       I2C_Write1ByteRegister(0xD0, 0x01,RTC1307._Minutes);
       I2C_Write1ByteRegister(0xD0, 0x02,RTC1307._Hours);
       I2C_Write1ByteRegister(0xD0, 0x04,RTC1307._Day);
       I2C_Write1ByteRegister(0xD0, 0x05,RTC1307._Month);
       I2C_Write1ByteRegister(0xD0, 0x06,RTC1307._Year);
   }
}

void APP_INT1_ISR(void){
   if(option_counter==1){ /*for seconds*/
       seconds_counter++;
       if(seconds_counter>59){
           seconds_counter=0;
       }
       convert_int_to_BCD(seconds_counter,&RTC1307._Seconds);
   }
   else if(option_counter==2){ /*for minutes*/
       minutes_counter++;
       if(minutes_counter>59){
           minutes_counter=0;
       }
       convert_int_to_BCD(minutes_counter,&RTC1307._Minutes);
   }
   else if(option_counter==3){ /*for hours*/
       hours_counter++;
       if(hours_counter>23){
           hours_counter=0;
       }
       convert_int_to_BCD(hours_counter,&RTC1307._Hours);
   }
   else if(option_counter==4){ /*for day*/
       day_counter++;
       if(day_counter>30){
           day_counter=1;
       }
       convert_int_to_BCD(day_counter,&RTC1307._Day);
   }
   else if(option_counter==5){ /*for month*/ 
       month_counter++;
       if(month_counter>12){
           month_counter=1;
       }
       convert_int_to_BCD(month_counter,&RTC1307._Month);
   }
   else if(option_counter==6){ /*for year*/
       year_counter++;
        if(year_counter>99){
           year_counter=1;
       }
       convert_int_to_BCD(year_counter,&RTC1307._Year);
   }
}
void main(void)
{
    //Initialize the device
    _Initialize();
    
    while (1)
    {
        if(option_counter==0){ /*for seconds*/
            /*getting TIME value and display it on the LCD*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            RTC1307 = RealTimeClockDS1307_Get_Date_Time();
            lcd_send_string_pos(&lcd,1,1,"TIME:");
            convert_BCD_to_int(RTC1307._Hours,&hours_counter);
            lcd_send_number_pos(&lcd,1,7,hours_counter);
            lcd_send_char_data_pos(&lcd,1,9,':');
            convert_BCD_to_int(RTC1307._Minutes,&minutes_counter);
            lcd_send_number_pos(&lcd,1,10,minutes_counter);
            lcd_send_char_data_pos(&lcd,1,12,':');
            convert_BCD_to_int(RTC1307._Seconds,&seconds_counter);
            lcd_send_number_pos(&lcd,1,13,seconds_counter);
            
            /*getting DATE value and display it on the LCD*/
            lcd_send_string_pos(&lcd,2,1,"DATE:");
            convert_BCD_to_int(RTC1307._Day,&day_counter);
            lcd_send_number_pos(&lcd,2,7,day_counter);
            lcd_send_char_data_pos(&lcd,2,9,'/');
            convert_BCD_to_int(RTC1307._Month,&month_counter);
            lcd_send_number_pos(&lcd,2,10,RTC1307._Month);
            lcd_send_char_data_pos(&lcd,2,12,'/');
            convert_BCD_to_int(RTC1307._Year,&year_counter);
            lcd_send_number_pos(&lcd,2,13,year_counter);
            __delay_ms(500);
        }
        else if(option_counter==1){
            /*seconds seconds on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"seconds:");
            lcd_send_number_pos(&lcd,1,10,seconds_counter);
            __delay_ms(500);
        }
        else if(option_counter==2){
            /*display minutes on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"minutes:");
            lcd_send_number_pos(&lcd,1,10,minutes_counter);
            __delay_ms(500);
        }
        else if(option_counter==3){
            /*display hours on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"hours:");
            lcd_send_number_pos(&lcd,1,8,hours_counter);
            __delay_ms(500);
        }
        else if(option_counter==4){
            /*display day on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"day:");
            lcd_send_number_pos(&lcd,1,6,day_counter);
            __delay_ms(500);
        }
        else if(option_counter==5){
            /*display month on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"month:");
            lcd_send_number_pos(&lcd,1,8,month_counter);
            __delay_ms(500);
        }
        else if(option_counter==6){
            /*display year on the LCD while updating it*/
            lcd_send_command(&lcd,_LCD_CLEAR);
            lcd_send_string_pos(&lcd,1,1,"year:");
            lcd_send_number_pos(&lcd,1,7,year_counter);
            __delay_ms(500);
        }
    }
}
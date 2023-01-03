/*
 * The Safe.c
 *
 * Created: 12/26/2022 11:52:20 AM
 * Author : Ahmed Hassan
 */ 

#include <avr/io.h>
#define F_CPU 8000000UL
#include "util/delay.h"
#include "LCD.h"
#include "Keypad.h"
#include "EEPROM.h"
#define EEPROM_STATUS_LOCATION	  0X10
#define EEPROM_PASSWORD_LOCATION1 0X11
#define EEPROM_PASSWORD_LOCATION2 0X12
#define EEPROM_PASSWORD_LOCATION3 0X13
#define EEPROM_PASSWORD_LOCATION4 0X14
#define DEFAULT 0xFF
#define Max_TRIES 3
int main(void)
{
	char arr[4];
	char value = NOTPRESSED;
	char flag=0 , i ;
	char Tries = Max_TRIES;
	LCD_intial();
	keypad_vInit();
	if (EEPROM_read(EEPROM_STATUS_LOCATION)==DEFAULT)
	{
		LCD_send_string("set pass:");
		for(i=0;i<=3;i++)
		{
			do 
			{
				value= keypad_u8check_press();
			} while (value==NOTPRESSED);
			LCD_send_char(value);
			_delay_ms(500);
			LCD_move_cursor(1,10+i);
			LCD_send_char('*');
			EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,value);
		}
		EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
	}
	
    while (flag==0) //tries of password
    {
		arr[0]=arr[1]=arr[2]=arr[3];
		LCD_clear_screen();
		LCD_send_string("check pass:");
		for(i=0;i<=3;i++)
		{
			do
			{
				arr[i]= keypad_u8check_press();
			} while (arr[i]==NOTPRESSED);
			LCD_send_char(arr[i]);
			_delay_ms(500);
			LCD_move_cursor(1,12+i);
			LCD_send_char('*');
		}
		if (EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0]&&EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[2]&&EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[2]&&EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[3])
		{
			LCD_clear_screen();
			LCD_send_string("right password");
			LCD_move_cursor(2,1);
			LCD_send_string("safe opened");
			flag=1;
		}
		else
		{
			Tries=Tries-1;
			if (Tries>0)
			{
				LCD_clear_screen();
				LCD_send_string("wrong password");
				//_delay_ms(1000);
				LCD_move_cursor(2,1);
				LCD_send_string("tries left=");
				LCD_send_char(Tries+48);
				_delay_ms(2000);
			}
			else
			{
				LCD_clear_screen();
				LCD_send_string("wrong password");
				LCD_move_cursor(2,1);
				LCD_send_string("safe closed");
				flag=1;
				
			}
		}
    }
}


/*
 * Keypad.c
 *
 * Created: 12/25/2022 1:04:04 PM
 *  Author: User
 */ 
#include "Keypad.h"
void keypad_vInit(){	DIO_SET_PIN_DIR('B',4,1);	DIO_SET_PIN_DIR('B',5,1);	DIO_SET_PIN_DIR('B',6,1);	DIO_SET_PIN_DIR('B',7,1);	DIO_SET_PIN_DIR('D',2,0);	DIO_SET_PIN_DIR('D',3,0);	DIO_SET_PIN_DIR('D',4,0);	DIO_SET_PIN_DIR('D',5,0);	DIO_venable_Pullup('D',2,1);	DIO_venable_Pullup('D',3,1);	DIO_venable_Pullup('D',4,1);	DIO_venable_Pullup('D',5,1);	}char keypad_u8check_press(){	char arr[4][4]={{'7','8','9','/'},{'4','5','6','*'},{'1','2','3','-'},{'A','0','=','+'}};	char row,coloumn,x;	char returnval=NOTPRESSED;	for(row=0;row<4;row++)	{		DIO_WRITE_PIN('B',4,1);		DIO_WRITE_PIN('B',5,1);		DIO_WRITE_PIN('B',6,1);		DIO_WRITE_PIN('B',7,1);		DIO_WRITE_PIN('B',row+4,0);	for(coloumn=0;coloumn<4;coloumn++)	{		x=DIO_U8READ_PIN('D',(coloumn+2));		if (x==0)		{			returnval=arr[row][coloumn];			break;		}			}		if (x==0)		{			break;		}	}	return returnval ; }				
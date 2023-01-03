/*
 * EEPROM.h
 *
 * Created: 12/12/2022 2:47:53 PM
 *  Author: Ahmed Hassan
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
void EEPROM_write(unsigned short address , unsigned char data);
unsigned char EEPROM_read(unsigned short address);
#endif /* EEPROM_H_ */
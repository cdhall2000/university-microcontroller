/* 
	Editor: https://www.visualmicro.com/
			visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
			the contents of the _vm sub folder can be deleted prior to publishing a project
			all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
			note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: ATmega328P (Arduino Nano), Platform=avr, Package=arduino
*/

#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
#define ARDUINO 108010
#define ARDUINO_MAIN
#define F_CPU 16000000L
#define __AVR__
#define F_CPU 16000000L
#define ARDUINO 108010
#define ARDUINO_AVR_NANO
#define ARDUINO_ARCH_AVR
void init_pins(void);
uint8_t keypressed();
char keypad_read(char lastchar);
char assignNote(char key);
void inc_counter(void);
void init_interrupts(void);
int main(void);

#include "pins_arduino.h" 
#include "arduino.h"
#include "ecuProject.ino"
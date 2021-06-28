/* DEFINES */

#define _DEBUG 1
#define USE_ARDUINO_LCD 1

#if !defined(__AVR_ATmega328P__) && !defined(__AVR_ATmega168P__) && _DEBUG
#   define BROKEN_DEFINES 1
#   define MPU_CPU 16000000
#endif


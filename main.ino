/*
    Author: Conor Hall
    Date of Submission: 25/10/2019
    Description
*/

/* INCLUDES */

//Main Header Includes - Contains definitions for main.ino
#include "main.h"

//C++ Includes
#include <stdio.h>
#include <math.h>

//AVR Includes
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

#if BROKEN_DEFINES
#  include <avr/iom328p.h>
#  include <avr/iom328p.h>
#endif

#if USE_ARDUINO_LCD
#   include <LiquidCrystal.h> //LCD for arduino
#else 
#   include "lib\libnerdkits\lcd.h"
#endif

#if BROKEN_DEFINES || __AVR_ATmega328P__
#   include <Arduino.h> 
#endif

#if BROKEN_DEFINES || __AVR_ATmega168P__ 
//University Library Includes
#   include "lib\libnerdkits\delay.h"
#   include "lib\libnerdkits\uart.h"
#   include "lib\libnerdkits\lcd.h"
#endif

//Sound Effect Includes
#include "lib\sfx\zap.h"
#include "lib\sfx\ray.h"
#include "lib\sfx\blast.h"

/*
   PINS: Arduino Specific, These pins need to be changed for the conversion to the ATmega168
   LCD RS = D12
   LCD EN = D6
   LCD D4 = D5
   LCD D5 = D4
   LCD D6 = D3
   LCD D7 = D2


   PINS: These pins should be ok for ATmega168
   PINB3 = D11 - Speaker Pin OUTPUT
   PINC1 = A1 - Column Pin 1 OUTPUT
   PINC2 = A2 - Column Pin 2 OUTPUT
   PINC3 = A3 - Column Pin 3 OUTPUT
   PINC4 = A4 - Row Pin 1 INPUT_PULLUP
   PINC5 = A5 - Row Pin 2 INPUT_PULLUP
   PINB1 = D9 - Row Pin 3 INPUT_PULLUP
   PINB2 = D10 - Row Pin 4 INPUT_PULLUP

   TO READ THE PINPAD THE OUTPUT PINS NEED TO BE SINKING AND THE INPUTS NEED TO HAVE THEIR PULLUP RESISTORS ACTIVATED.
*/


//Global variables
const uint8_t rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2; //ARDUINO LCD PINS
volatile MenuObject Menu; //This is the object for the menu
static const uint8_t MENU_ROOT = 0;
static const uint8_t MENU_INSTANT = 1;
static const uint8_t MENU_SEQUENCE = 2;
static const uint8_t MENU_SFX = 3;
static const uint8_t MENU_DEBUG = 4;

const uint8_t keypad_colomb_1 = PINC1;
const uint8_t keypad_colomb_2 = PINC2;
const uint8_t keypad_colomb_3 = PINC3;
const uint8_t keypad_row_1 = PINC4;
const uint8_t keypad_row_2 = PINC5;
const uint8_t keypad_row_3 = PINB1;
const uint8_t keypad_row_4 = PINB2;

const uint8_t Speaker = PINB3;

//Musical Note Declarations
uint8_t NOTE_C4 = 118;
uint8_t NOTE_D4 = 105;
uint8_t NOTE_E4 = 95;
uint8_t NOTE_F4 = 88;
uint8_t NOTE_G4 = 79;
uint8_t NOTE_A4 = 70;
uint8_t NOTE_B4 = 62;

#if defined(__AVR_ATmega328P__) //ARDUINO NANO (ATmega328p) DEFINITIONS
    const int MPU_CPU = 16000000; //uC frequency in Hz

#elif defined(__AVR_ATmega168P__) //UNIVERSITY UC (ATmega168p) DEFINITIONS
    const int MPU_CPU = 14745600;
#endif



class MenuObject {
    private:
        volatile uint8_t current_menu_context; 
        //The context value of the menu. This determines what function will be executed.
        volatile int timer2_ovf_counter; //TODO: Figure out what this is.

    public:
        uint8_t get_menu_context(void) { //MenuObject Context Getter
            return current_menu_context;
        }
        uint8_t set_menu_context(uint8_t context) { //MenuObject Context Setter
            if (context != MENU_ROOT && context != MENU_INSTANT && context != MENU_SEQUENCE && context != MENU_SFX) {
                return 0;
            } else {
                current_menu_context = context;
                return 1;
            }
        }

        int get_timer2_ovf(void) { //MenuObject Int Count Getter
            return timer2_ovf_counter;
        }
        uint8_t set_timer2_ovf(int int_count_val) { //MenuObject Int Count Setter
            int temp = timer2_ovf_counter;
            timer2_ovf_counter = int_count_val;
            return;
        }

        MenuObject() { //MenuObject Constructor
            current_menu_context = MENU_ROOT;
            timer2_ovf_counter = 0;
        }
};



ISR(TIMER2_COMPA_vect) {
    uint8_t menu_context = Menu.get_menu_context(); //Get the menu_context into a temp var.

    if (menu_context == MENU_INSTANT || menu_context == MENU_SEQUENCE) { 
        if (menu_context == MENU_SEQUENCE) { 
            inc_counter(); 
        }
        PORTB ^= (1 << PINB3); //PORTB XOR 0000-1000 : This toggles the output pin PINB3
    }
    if (menu_context == MENU_SFX) { 
        PORTB |= (1 << PINB3); //PORTB OR 0000-1000 : This sets the output pin PINB3 high
    }
}

ISR(TIMER2_OVF_vect) {
    uint8_t menu_context = Menu.get_menu_context(); //Get the menu_context into a temp var.

    if (menu_context == MENU_SEQUENCE) { inc_counter(); } 
    
    if (menu_context == MENU_SFX) { PORTB &= ~(1 << PINB3); } //PORTB AND 1111-0111 : This sets the output pin PINB3 low

    if (Menu.get_timer2_ovf() == 0) { Menu.set_timer2_ovf(1); } //TODO: Figure this one out
}


void halt(unsigned int ms) {
    #if defined(__AVR_ATmega328P__)
        delay(ms);

    #elif defined(__AVR_ATmega168P__)
        delay_ms(ms);

    #elif defined(BROKEN_DEFINES)
        delay(ms);
    #endif
}

void halt_us(unsigned int us) {
    #if defined(__AVR_ATmega328P__)
        delayMicroseconds(us);

    #elif defined(__AVR_ATmega168P__)
        delay_us(us);

    #elif defined(BROKEN_DEFINES)
        delayMicroseconds(us);
    #endif

}


void set_pin_registers(void) {
    /*  Pin Port Truth Table
        DDxn : PORTxn : State
        0 : 0 : Input (no pullup)
        0 : 1 : Input (pullup)
        1 : 0 : Output lower
        1 : 1 : Output high

        PINxn = IO registers
        DDxn = Data direction registers (1 output, 0 input)
        PORTxn = IO mode registers (1 high, 0 low)
    */
    //Set Pin IO Modes
    DDRC |= ((1 << keypad_colomb_1) | (1 << keypad_colomb_2) | (1 << keypad_colomb_3)); //PINC1-3 = Column Output Pins
    DDRC &= ~((1 << keypad_row_1) | (1 << keypad_row_2)); //PINC4+5 = Row Input Pins
    DDRB &= ~((1 << keypad_row_3) | (1 << keypad_row_4)); // PINB1+2 = Row Input Pins
    DDRB |= (1 << Speaker); //PINB3 = Speaker Output Pin

    //Set Input Pullup Resistors
    PORTC |= ((1 << keypad_row_1) | (1 << keypad_row_2)); // PINC4+5 = Row Input Pins Internal Pullup Resistors
    PORTB |= ((1 << keypad_row_3) | (1 << keypad_row_4)); // PINB1+2 = Row Input Pins Internal Pullup Resistors
}

void set_global_notes(void) {
    /* 
        note freq = (uc_freq)/(2*prescale*(1+OCRA))
        note frequency = (microcontroller frequency)/(2*prescaler*(OCRA + 1))
        OCRA+1 = (microcontroller frequency/note frequency)/(2*prescaler)

        Calculating the OCRA value for notes C4-B4 using the MPU_CPU value
     */
    float notes[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440, 493.88}; //Array of our note frequencies
    uint8_t* keys[] = {&NOTE_C4, &NOTE_D4, &NOTE_E4, &NOTE_F4, &NOTE_G4, &NOTE_A4, &NOTE_B4}; //Pointer array of our note OCRA values
    for (int i = 0; i < (sizeof(notes)/sizeof(notes[i])); i++) {
        double first_holder = (((MPU_CPU/notes[i])/512)-1); //Calculate OCRA value
        double resultant = round(first_holder); //Round OCRA value
        if (resultant > 0 && resultant < 255) { //Check OCRA is within bounds
            *keys[i] = (uint8_t)resultant; //Set note OCRA value to uint8_t result
        }
    }
}

uint8_t check_for_keypress(void) {
    // checks to see if any key has been pressed
    // Returns a 1 (true) if a key has been pressed, 0 if not pressed
    // Set column output pins low (sinking), so if the input row pins are pulled low then contact is made
    uint8_t row_input;
    PORTC &= ~(0x0E); //Set all column pins low
    
    halt_us(10);                           // delay to allow signals to settle
    row_input = (PINC >> 4); //Read in PINC and shift right 4 to get PINC 4, 5 and 6 in first 3 bits
    //row_input = xxxx-x:C6:C5:C4
    row_input |= ((PINB << 1) & (1 << 2 | 1 << 3)); //Read PINB while shift+masking to get PINB 1 and 2 on positions 2+3 of row_input 
    //row_input OR ((PINB << 1 AND (0000-1100))==xxxx-B2:B1:xx)
    row_input &= (1 << PINC3 | 1 << PINC2 | 1 << PINC1 | 1 << PINC0); // mask out other bits [4-7] 
    //row_input = xxxx-B2:B1:C5:C4
    //We expect to get the value 0000-1111=0x0F=15 if no keys are pressed

    if (row_input == 0x0F) {
        //No keys are pressed.
        return 0;
    } else {
        //A key is pressed!
        return 1;
    }
}


uint8_t get_row_input(uint8_t active_colomb = 0) {
    uint8_t row_input;                           //Our row_input variable
    if (active_colomb == 0) { PORTC &= (0xF1); } // set all colomb output pins to low
    if (active_colomb == 1) { PORTC &= (0xFD); } // set all to high and colomb_1 to low
    if (active_colomb == 2) { PORTC &= (0xFB); } // set all to high and colomb_2 to low
    if (active_colomb == 3) { PORTC &= (0xF7); } // set all to high and colomb_3 to low
    halt_us(10);                                 //wait for signals to settle
    row_input = (PINC >> 4);                     //Get the row_input
    row_input |= ((PINB << 1) & (1 << 2 | 1 << 3));
    row_input &= (1 << PINC3 | 1 << PINC2 | 1 << PINC1 | 1 << PINC0);
    return row_input;
}

char keypad_read(char lastchar) {
    // read from keypad
    // (assumes key has been pressed)
    // returns chars 0..9, # , *
    // takes in lastchar, and returns that if invalid read from keypad

    uint8_t row_input; //Our row_input variable
    char key_char = '$'; //Our key pressed variable; Initialise to $ (out of bounds char)

    if (key_char == '$') {
        PORTC |= ((1 << keypad_colomb_3) | (1 << keypad_colomb_2)); // set colombs 2 + 3 high set 1 low
        PORTC &= ~(1 << keypad_colomb_1);
        halt_us(10); //wait for signals to settle
        row_input = (PINC >> 4); //Get the row_input
        row_input |= ((PINB << 1) & (1 << 2 | 1 << 3));
        row_input &= (1 << PINC3 | 1 << PINC2 | 1 << PINC1 | 1 << PINC0);

        switch (row_input) {
        case 7: key_char = '3';
            break;
        case 11: key_char = '6';
            break;
        case 13: key_char = '9';
            break;
        case 14: key_char = '#';
            break;
        default: key_char = '$';
            break;
        }
    }

    if (key_char == '$') {                   // if still not valid key
        PORTC |= ((1 << keypad_colomb_3) | (1 << keypad_colomb_1)); // set  other 2 high
        PORTC &= ~(1 << keypad_colomb_2);             // set PINC1 low - check column 2
        halt_us(10);                       // delay to allow signals to settle

        // Read value from Pins on PortC
        row_input = (PINC >> 4);
        row_input |= ((PINB << 1) & (1 << 2 | 1 << 3));
        row_input &= (1 << PINC3 | 1 << PINC2 | 1 << PINC1 | 1 << PINC0); // mask out other bits [4-7]

        switch (row_input) {
        case 7: key_char = '2';
            break;
        case 11: key_char = '5';
            break;
        case 13: key_char = '8';
            break;
        case 14: key_char = '0';
            break;
        default: key_char = '$';
            break;
        }
    }

    if (key_char == '$') {       // if still not valid key
        PORTC |= ((1 << keypad_colomb_2) | (1 << keypad_colomb_1)); // set  other 2 high
        PORTC &= ~(1 << keypad_colomb_3);    // set PINC2 low - check column 3
        halt_us(10);              // delay to allow signals to settle

        // Read value from Pins on PortC
        row_input = (PINC >> 4);
        row_input |= ((PINB << 1) & (1 << 2 | 1 << 3));
        row_input &= (1 << PINC3 | 1 << PINC2 | 1 << PINC1 | 1 << PINC0); // mask out other bits [4-7]

        switch (row_input) {
        case 7: key_char = '1';
            break;
        case 11: key_char = '4';
            break;
        case 13: key_char = '7';
            break;
        case 14: key_char = '*';
            break;
        default: key_char = '$';
            break;
        }
    }

    if (key_char != '$') {     // if valid character
        lastchar = key_char;    // update last char
    }
    return lastchar;
}

char assignNote(char key) {
    if (key == '$' || key == '8' || key == '9' || key == '*' || key == '0' || key == '#') {
        //Serial.println("Wrong Key");
        return '&';
    } else { //break if not a valid key

        char returner = '?';

        switch (key) {
        case '1': OCR2A = NOTE_C4; returner = 'C';
            break;
        case '2': OCR2A = NOTE_D4; returner = 'D';
            break;
        case '3': OCR2A = NOTE_E4; returner = 'E';
            break;
        case '4': OCR2A = NOTE_F4; returner = 'F';
            break;
        case '5': OCR2A = NOTE_G4; returner = 'G';
            break;
        case '6': OCR2A = NOTE_A4; returner = 'A';
            break;
        case '7': OCR2A = NOTE_B4; returner = 'B';
            break;

        default: OCR2A = NOTE_E4; returner = 'E';
            break;
        }

        TIMSK2 |= (1 << 1); //enable interuppts
        TCCR2B |= (1 << 7);
        return returner;
    }
}

int tCount = 0;
int countMax = 600;

void inc_counter(void) {
    tCount++;

    countMax = (MPU_CPU / (OCR2A * 256));

    if (tCount >= countMax) {
        TIMSK2 &= ~(1 | (1 << 1) | (1 << 2)); //disable counter
        TCCR2B |= (1 << 7); //Force compare

        tCount = 0;

    }
}

void tone_interrupts(void) {

    TCCR2A = B00000010;
    TCCR2B = B00000110; //set prescaler to 256
    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);

    OCR2A = 95;

}

void pmw_interrupts(void) {

    TCCR2A = B00000011;
    TCCR2B = B00000010; //set prescaler to 8
    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);

    OCR2A = 95;
}

int main(void) {
    init();      //Only Required for Arduino
    set_pin_registers(); //Initiate speaker and keypad

    //Start LCD
    LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
    lcd.begin(16, 2);
    lcd.print("Power on.");



    char temp_char = '$';
    char note = '?';
    char triggerLCD = 0;

    uint8_t temp_int = 25;
    int _menu = 1; //what window of the menu is currently being displayed

     //Spin wheels for a bit, seems to make things more stable
      /*
    TIMSK2 |= (1 << 1); //enable interuppts
    TCCR2B |= (1 << 7); //reset timer
  */
    Menu.set_menu_context(0);
    int datastrobe = 0;
    halt(2000);
    while (1)   {
        //------------------------------------------------------------------------------------------------------
        if (Menu.get_menu_context() == 0)     { //Main menu where you select mode

            lcd.clear();
            lcd.home();

            lcd.print("Select Function:");
            halt(2000);
            lcd.clear();
            lcd.print("1. Tones 2. Seq");
            lcd.setCursor(0, 1);
            lcd.print("3. SFX Player");

            char menuTemp = '8';
            while (Menu.get_menu_context() == 0)       { //Contain everything
                menuTemp = keypad_read(menuTemp);
                if (menuTemp == '1')         {
                    Menu.set_menu_context(1);
                    lcd.clear();
                }
                if (menuTemp == '2')         {
                    Menu.set_menu_context(2);
                    lcd.clear();
                }
                if (menuTemp == '3')         {
                    Menu.set_menu_context(3);
                    lcd.clear();
                }
                if (menuTemp == '4')         {
                    Menu.set_menu_context(4);
                    lcd.clear();
                }
            }
        }

        //------------------------------------------------------------------------------------------------------
        if (Menu.get_menu_context() == 1)     { //Function 1 PLAY NOTES AS PRESSED
            tone_interrupts(); // Initiate Interrupt Register
            //TIMSK2 |= (1 << 1); //Turn on interrupts

            lcd.clear();
            lcd.print("Init Interrupts");

            for (int i = 0; i <= 20000; i++)       {
                ;
            }

            lcd.setCursor(0, 1);
            lcd.print("Function 1");
            lcd.home();

            while (Menu.get_menu_context() == 1)       {
                temp_int = check_for_keypress();
                halt_us(5);



                if (!(TIMSK2 >> 1))         { //If no interrupts enabled

                    temp_char = keypad_read(temp_char);
                    halt_us(5);
                    if (temp_char == '9')           {
                        Menu.set_menu_context(0);
                        lcd.clear();
                        lcd.print("Returning...");
                        TIMSK2 &= ~(1 | (1 << 1) | (1 << 2)); //disable counter
                        TCCR2B |= (1 << 7);
                        halt(200);
                    }
                    note = assignNote(temp_char);
                    if ((temp_char == '1' || temp_char == '2' || temp_char == '3' || temp_char == '4' || temp_char == '5' || temp_char == '6' || temp_char == '7') && triggerLCD)           {
                        lcd.clear();
                        lcd.home();

                        lcd.print("Note ");
                        lcd.print(note);
                        lcd.print("4 playing.");
                        triggerLCD = 0;
                    }
                    if (!triggerLCD && temp_char == '$')           {
                        lcd.clear();
                        lcd.home();

                        //lcd.print("No note playing.");
                        lcd.print("No tone playing.");
                        lcd.setCursor(0, 1);
                        lcd.print("Key 9 to return");
                        triggerLCD = 1;
                    }
                }

                if (TIMSK2 >> 1)         {
                    temp_int = check_for_keypress();
                    if (temp_int == 15)           {
                        TIMSK2 &= ~(1 | (1 << 1) | (1 << 2)); //disable counter
                        TCCR2B |= (1 << 7);                   //Force compare
                    }
                }
                temp_char = '$';
            }
        }


        //------------------------------------------------------------------------------------------------------
        if (Menu.get_menu_context() == 2)     { //Function 2
            tone_interrupts(); // Initiate Interrupt Register
            //TIMSK2 |= (1 << 1); //Turn on interrupts

            lcd.clear();
            lcd.print("Init Interrupts");

            for (int i = 0; i <= 1000; i++)       {
                ;
            }


            lcd.clear();
            lcd.print("Enter tone:");
            lcd.setCursor(0, 1);
            lcd.print("Function 2");

            while (check_for_keypress() != 15)       {
                ;
            }

            temp_char = '$';

            char sequence[6];
            int s_count = 0;

            while (Menu.get_menu_context() == 2)       {
                temp_char = keypad_read(temp_char);

                if (temp_char == '1' || temp_char == '2' || temp_char == '3' || temp_char == '4' || temp_char == '5' || temp_char == '6' || temp_char == '7')         {
                    sequence[s_count] = temp_char;
                    lcd.setCursor((11 + s_count), 0);
                    lcd.print(sequence[s_count]);


                    if (s_count >= 4) {

                        lcd.setCursor(0, 1);
                        lcd.print("               ");
                        lcd.setCursor(0, 1);

                        for (int i = 0; i <= 4; i++)             {
                            temp_char = assignNote(sequence[i]);
                            lcd.print(temp_char);
                            if (i != 4) { lcd.print("4,"); } else { lcd.print("4"); }
                            halt(10);
                            while (TIMSK2 >> 1) { ; }
                        }
                        halt(1000);
                        s_count = 0;
                        lcd.clear();
                        lcd.print("Enter tone:");
                        lcd.setCursor(0, 1);
                        lcd.print("Key 9 to return");
                    } else { s_count++; }
                    //temp_char = ''
                }

                if (temp_char == '9')         {
                    lcd.clear();
                    lcd.print("Returning...");
                    Menu.set_menu_context(0);
                }

                while (check_for_keypress() != 15)         {
                    ;
                }

                temp_char = '$';
            }
        }


        //------------------------------------------------------------------------------------------------------
        if (Menu.get_menu_context() == 3)     { //Function 3
            TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);

            pmw_interrupts(); // Initiate Interrupt Register
            //TIMSK2 |= (1 << 1); //Turn on interrupts

            lcd.clear();
            lcd.print("Init Interrupts");
            //TIMSK2 |= (1 << 1);
            for (int i = 0; i <= 1000; i++)       {
                ;
            }

            lcd.clear();
            lcd.print("1. Zap - 2. Ray");
            lcd.setCursor(0, 1);
            lcd.print("3. Blast");
            temp_int = check_for_keypress();
            int i = 0;
            int i_count = 0;
            int gap = 0;

            char temp_pressed = 'a';

            while (Menu.get_menu_context() == 3)       {
                while (temp_int != 15) { temp_int = check_for_keypress(); halt(1); }


                //OCR2A = 5;
                temp_char = keypad_read(temp_char);
                temp_int = check_for_keypress();

                lcd.clear();
                lcd.print("Reading Key");
                lcd.setCursor(0, 1);
                lcd.print("'9' to return");


                if (temp_char == '1')         {
                    TIMSK2 |= (1 << 1 | 1);
                    temp_pressed = keypad_read(temp_pressed);
                    Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Zap");
                    while (i < zap_length)           {
                        temp_char = pgm_read_byte(&zap_data[i]);
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        halt_us(1000);
                    }
                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                    halt(500);
                    temp_char = 'a';
                }

                if (temp_char == '2')         {
                    TIMSK2 |= (1 << 1 | 1);
                    temp_pressed = keypad_read(temp_pressed);
                    Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Ray");
                    while (i < ray_length)           {
                        temp_char = pgm_read_byte(&ray_data[i]);
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        halt_us(1000);
                    }
                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                    halt(500);
                    temp_char = 'a';
                }

                if (temp_char == '3')         {
                    TIMSK2 |= (1 << 1 | 1);
                    temp_pressed = keypad_read(temp_pressed);
                    Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Blast");
                    while (i < blast_length)           {
                        temp_char = pgm_read_byte(&blast_data[i]);
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        halt_us(1000);
                    }
                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                    halt(500);
                    temp_char = 'a';
                }



                if (temp_char == '4')         {
                    TIMSK2 |= (1 << 1 | 1);
                    temp_pressed = temp_char;
                    i_count = check_for_keypress();
                    //Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Zap");
                    lcd.setCursor(0, 1);
                    if (gap == 0)           {
                        lcd.print("0 second gap");
                    } else {
                        lcd.print("0.");
                        lcd.print(gap);
                        lcd.print(" second gap");
                    }
                    while (i <= zap_length && i_count != 15)           {
                        temp_pressed = keypad_read(temp_pressed);
                        i_count = check_for_keypress();
                        for (int jay = 0; jay < 4000; jay++) { ; }
                        temp_char = pgm_read_byte(&zap_data[i]);
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        if (i == zap_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); halt(gap * 100); TIMSK2 |= (1 << 1 | 1); }
                        halt_us(1000);
                    }

                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                    temp_char = 'a';
                }



                if (temp_char == '5')         {
                    TIMSK2 |= (1 << 1 | 1);
                    i_count = check_for_keypress();
                    Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Ray");
                    lcd.setCursor(0, 1);
                    if (gap == 0)           {
                        lcd.print("0 second gap");
                    } else {
                        lcd.print("0.");
                        lcd.print(gap);
                        lcd.print(" second gap");
                    }
                    while (i <= ray_length && i_count != 15)           {
                        temp_char = pgm_read_byte(&ray_data[i]);
                        i_count = check_for_keypress();
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        if (i == ray_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); halt(gap * 100); TIMSK2 |= (1 << 1 | 1); }
                        halt_us(1000);
                    }
                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                }


                if (temp_char == '6')         {
                    TIMSK2 |= (1 << 1 | 1);
                    i_count = check_for_keypress();
                    Menu.set_timer2_ovf(1);
                    lcd.clear();
                    lcd.print("SFX Blast");
                    lcd.setCursor(0, 1);
                    if (gap == 0)           {
                        lcd.print("0 second gap");
                    } else {
                        lcd.print("0.");
                        lcd.print(gap);
                        lcd.print(" second gap");
                    }
                    while (i <= blast_length && i_count != 15)           {
                        temp_char = pgm_read_byte(&blast_data[i]);
                        i_count = check_for_keypress();
                        temp_int = (int)temp_char;
                        OCR2A = temp_int;
                        //lcd.clear();
                        //lcd.print(i);
                        i++;
                        if (i == blast_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); halt(gap * 100); TIMSK2 |= (1 << 1 | 1); }
                        halt_us(1000);
                    }
                    i = 0;
                    TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
                }

                if (temp_char == '9')         {
                    lcd.clear();
                    lcd.print("Returning...");
                    Menu.set_menu_context(0);
                }

                if (temp_char == '*') {
                    if (gap > 0) { gap--; }
                    lcd.clear();
                    if (gap == 0)           {
                        lcd.print("0 second gap");
                    } else {
                        lcd.print("0.");
                        lcd.print(gap);
                        lcd.print(" second gap");
                    }

                    i_count = check_for_keypress();
                    while (i_count != 15) { i_count = check_for_keypress(); halt(1); }
                    halt(500);
                    temp_char = 'a';

                }

                if (temp_char == '#') {
                    if (gap < 9) { gap++; }

                    lcd.clear();
                    lcd.print("0.");
                    lcd.print(gap);
                    lcd.print(" second gap");
                    i_count = check_for_keypress();
                    while (i_count != 15) { i_count = check_for_keypress(); halt(1); }
                    halt(500);
                    temp_char = 'a';
                }

                halt(100);
            }
        }

        if (Menu.get_menu_context() == 4) { //Function 4
            temp_char = keypad_read(temp_char);
            temp_int = check_for_keypress();
            lcd.clear();
            lcd.print(temp_char);
            lcd.setCursor(0, 1);
            lcd.print(temp_int);
            halt(100);
        }

    }
    return 1;
}

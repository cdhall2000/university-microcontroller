#include <stdio.h>
#include <math.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <inttypes.h>

/*
#include "../libnerdkits/delay.h"
#include "../libnerdkits/lcd.h"
#include "../libnerdkits/uart.h"
*/

#include <LiquidCrystal.h> //LCD for arduino

#include "zap.h"
#include "ray.h"
#include "blast.h"


/* ATmega168 Note Definitions
   #define C4 109
   #define D4 97
   #define E4 86
   #define F4 81
   #define G4 72
   #define A4 64
   #define B4 57
*/

//Arduino Note Definitions

#define C4  118
#define D4  105
#define E4  95
#define F4  88
#define G4  79
#define A4  70
#define B4  62



//#define MPU_CPU 14745600  //ATmega168 value
#define MPU_CPU 16000000 //Arduino ATmega328 value

/*
   PINS: Arduino Specific, These pins need to be changed for the conversion to the ATmega168
   LCD RS = D12
   LCD EN = D6
   LCD D4 = D5
   LCD D5 = D4
   LCD D6 = D3
   LCD D7 = D2


   PINS: These pins should be ok for ATmega168
   PB3 = D11 - Speaker Pin OUTPUT
   PC1 = A1 - Column Pin 1 OUTPUT
   PC2 = A2 - Column Pin 2 OUTPUT
   PC3 = A3 - Column Pin 3 OUTPUT
   PC4 = A4 - Row Pin 1 INPUT_PULLUP
   PC5 = A5 - Row Pin 2 INPUT_PULLUP
   PB1 = D9 - Row Pin 3 INPUT_PULLUP
   PB2 = D10 - Row Pin 4 INPUT_PULLUP



   TO READ THE PINPAD THE OUTPUT PINS NEED TO BE SINKING AND THE INPUTS NEED TO HAVE THEIR PULLUP RESISTORS ACTIVATED.
*/

//Stuff to delete for ATmega168 conversion
const int rs = 12, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;

//int _menu(0);

class Menu {
  int classMenu = 0;
  int intCounter = 0;

public:
  int cMenu(void);
  void cMenu(int);

  int icount(void);
  void icount(int);
};

int Menu::cMenu() 
{ 
  return classMenu;
}

void Menu::cMenu(int num) 
{ 
    int temp = classMenu; 
    classMenu = num; 
    return;
}

int Menu::icount(void) 
{
  return intCounter;
}

void Menu::icount(int num)
{
  int temp = intCounter;
  intCounter = num;
  return;
}

Menu global_menu;

ISR(TIMER2_COMPA_vect) {
  if (global_menu.cMenu() == 2) { inc_counter(); }
  if (global_menu.cMenu() == 1 || global_menu.cMenu() == 2) { PORTB ^= (1 << PB3); }
  if (global_menu.cMenu() == 3) { PORTB |= (1<<PB3); }

}

ISR(TIMER2_OVF_vect) {
  if (global_menu.cMenu() == 2) { inc_counter(); }
  if (global_menu.icount() == 0) { global_menu.icount(1); }
  if (global_menu.cMenu() == 3) { PORTB &= ~(1<<PB3); }
}

const uint8_t col_1 = PC1;
const uint8_t col_2 = PC2;
const uint8_t col_3 = PC3;
const uint8_t row_1 = PC4;
const uint8_t row_2 = PC5;
const uint8_t row_3 = PB1;
const uint8_t row_4 = PB2;

const uint8_t Speaker = PB3;

void init_pins(void) {

  DDRC |= (1 << col_1) | (1 << col_2) | (1 << col_3); //PC1-3 = Column Output Pins
  DDRC &= ~(1 << row_1); // PC4 = Row Input Pin
  DDRC &= ~(1 << row_2); // PC5 = Row Input Pin
  DDRB &= ~(1 << row_3); // PB1 = Row Input Pin
  DDRB &= ~(1 << row_4); // PB2 = Row Input Pin
  DDRB |= (1 << Speaker); //PB3 = Speaker Pin



  //PORTB &= ~(1 << Speaker); // PB3 - Speaker Set Low
  PORTC |= (1 << row_1); // PC4 = Row Input Pin Internal Pullup Resistor
  PORTC |= (1 << row_2); // PC5 = Row Input Pin Internal Pullup Resistor
  PORTB |= (1 << row_3); // PB1 = Row Input Pin Internal Pullup Resistor
  PORTB |= (1 << row_4); // PB2 = Row Input Pin Internal Pullup Resistor

}

/*
   PC0 - Column OUTPUT - 3
   PC1 - Column OUTPUT - 1
   PC2 - Column OUTPUT - 5
   PC3 - Row Input - 2
   PC4 - Row Input - 7
   PC5 - Row Input - 6


*/


uint8_t keypressed() {
  // checks to see if any key has been pressed
  // sets columns to 0, and checks if any row goes low
  // Returns a 1 (true) if a key has been pressed, 0 if not pressed

  // Set column output pins low, so input low if contact made

  //Serial.println("Keypressed() read");

  uint8_t rowvl;
  uint8_t kp;

  PORTC &= ~(1 << col_1 | 1 << col_2 | 1 << col_3 ); // set PC0, PC1 and PC2 low
  delayMicroseconds(10);                           // delay to allow signals to settle
  // Read value from Pins on PortC
  // Then shift right 3 to get pins3, 4 and 5 in first 3 bits
  rowvl =  (PINC >> 4);
  rowvl |= ((PINB << 1) & (1 << 2 | 1 << 3));
  rowvl &= (1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0); // mask out other bits [4-7]

  kp = rowvl;              // if 7, all high so no key

  return kp;

}



char keypad_read(char lastchar) {
  // read from keypad
  // (assumes key has been pressed)
  // returns keyval 0..9
  // takes in lastchar, and returns that if invalid read from keypad

  uint8_t rowval;
  char keych;     // Initialise to $

  keych = '$';

  PORTC |= ( (1 << col_3) | (1 << col_2)); // set  other 2 high
  PORTC &= ~(1 << col_1 );   // set PC0  low - check column 1
  delayMicroseconds(10); //Arduino delay
  //delay_us(10) // delay to allow signals to settle


  // Read value from Pins on PortC
  // Then shift right 3 to get pins3, 4 and 5 in first 3 bits
  rowval =  (PINC >> 4);
  rowval |= ((PINB << 1) & (1 << 2 | 1 << 3));
  rowval &= (1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0); // mask out other bits [4-7]

  switch (rowval) {
    case 7: keych = '3';
      break;
    case 11: keych = '6';
      break;
    case 13: keych = '9';
      break;
    case 14: keych = '#';
      break;
    default: keych = '$';
      break;
  }

  if (keych == '$') {                   // if still not valid key
    PORTC |= ( (1 << col_3) | (1 << col_1)); // set  other 2 high
    PORTC &= ~(1 << col_2 );             // set PC1 low - check column 2
    delayMicroseconds(10);                       // delay to allow signals to settle

    // Read value from Pins on PortC
    rowval =  (PINC >> 4);
    rowval |= ((PINB << 1) & (1 << 2 | 1 << 3));
    rowval &= (1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0); // mask out other bits [4-7]

    switch (rowval) {
      case 7: keych = '2';
        break;
      case 11: keych = '5';
        break;
      case 13: keych = '8';
        break;
      case 14: keych = '0';
        break;
      default: keych = '$';
        break;
    }
  }

  if (keych == '$') {       // if still not valid key
    PORTC |= ( (1 << col_2) | (1 << col_1)); // set  other 2 high
    PORTC &= ~(1 << col_3 );    // set PC2 low - check column 3
    delayMicroseconds(10);              // delay to allow signals to settle

    // Read value from Pins on PortC
    rowval =  (PINC >> 4);
    rowval |= ((PINB << 1) & (1 << 2 | 1 << 3));
    rowval &= (1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0); // mask out other bits [4-7]

    switch (rowval) {
      case 7: keych = '1';
        break;
      case 11: keych = '4';
        break;
      case 13: keych = '7';
        break;
      case 14: keych = '*';
        break;
      default: keych = '$';
        break;
    }
  }

  if (keych != '$')  {     // if valid character
    lastchar = keych;    // update last char
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
      case '1': OCR2A = C4; returner = 'C';
        break;
      case '2': OCR2A = D4; returner = 'D';
        break;
      case '3': OCR2A = E4; returner = 'E';
        break;
      case '4': OCR2A = F4; returner = 'F';
        break;
      case '5': OCR2A = G4; returner = 'G';
        break;
      case '6': OCR2A = A4; returner = 'A';
        break;
      case '7': OCR2A = B4; returner = 'B';
        break;

      default: OCR2A = E4; returner = 'E';
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

  countMax = (MPU_CPU/(OCR2A * 256));
    
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

int main(void)
{
  init();      //Only Required for Arduino
  init_pins(); //Initiate speaker and keypad

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
  global_menu.cMenu(0);
  int datastrobe = 0;
  delay(2000);
  while (1)
  {
    //------------------------------------------------------------------------------------------------------
    if (global_menu.cMenu() == 0)
    { //Main menu where you select mode

      lcd.clear();
      lcd.home();

      lcd.print("Select Function:");
      delay(2000);
      lcd.clear();
      lcd.print("1. Tones 2. Seq");
      lcd.setCursor(0, 1);
      lcd.print("3. SFX Player");

      char menuTemp = '8';
      while (global_menu.cMenu() == 0)
      { //Contain everything
        menuTemp = keypad_read(menuTemp);
        if (menuTemp == '1')
        {
          global_menu.cMenu(1);
          lcd.clear();
        }
        if (menuTemp == '2')
        {
          global_menu.cMenu(2);
          lcd.clear();
        }
        if (menuTemp == '3')
        {
          global_menu.cMenu(3);
          lcd.clear();
        }
        if (menuTemp == '4')
        {
          global_menu.cMenu(4);
          lcd.clear();
        }
      }
    }

    //------------------------------------------------------------------------------------------------------
    if (global_menu.cMenu() == 1)
    { //Function 1
      tone_interrupts(); // Initiate Interrupt Register
      //TIMSK2 |= (1 << 1); //Turn on interrupts

      lcd.clear();
      lcd.print("Init Interrupts");

      for (int i = 0; i <= 20000; i++)
      {
        ;
      }

      lcd.setCursor(0, 1);
      lcd.print("Function 1");
      lcd.home();

      while (global_menu.cMenu() == 1)
      {
        temp_int = keypressed();
        delayMicroseconds(5);

        

        if (!(TIMSK2 >> 1))
        { //If no interrupts enabled

          temp_char = keypad_read(temp_char);
          delayMicroseconds(5);
          if (temp_char == '9')
          {
            global_menu.cMenu(0);
            lcd.clear();
            lcd.print("Returning...");
            TIMSK2 &= ~(1 | (1 << 1) | (1 << 2)); //disable counter
            TCCR2B |= (1 << 7);
            delay(200);
          }
          note = assignNote(temp_char);
          if ((temp_char == '1' || temp_char == '2' || temp_char == '3' || temp_char == '4' || temp_char == '5' || temp_char == '6' || temp_char == '7' ) && triggerLCD)
          {
            lcd.clear();
            lcd.home();

            lcd.print("Note ");
            lcd.print(note);
            lcd.print("4 playing.");
            triggerLCD = 0;
          }
          if (!triggerLCD && temp_char == '$')
          {
            lcd.clear();
            lcd.home();

            //lcd.print("No note playing.");
            lcd.print("No tone playing.");
            lcd.setCursor(0, 1);
            lcd.print("Key 9 to return");
            triggerLCD = 1;
          }
        }

        if (TIMSK2 >> 1)
        {
          temp_int = keypressed();
          if (temp_int == 15)
          {
            TIMSK2 &= ~(1 | (1 << 1) | (1 << 2)); //disable counter
            TCCR2B |= (1 << 7);                   //Force compare
          }
        }
        temp_char = '$';
      }
    }
    

    //------------------------------------------------------------------------------------------------------
    if (global_menu.cMenu() == 2)
    { //Function 2
      tone_interrupts(); // Initiate Interrupt Register
      //TIMSK2 |= (1 << 1); //Turn on interrupts

      lcd.clear();
      lcd.print("Init Interrupts");

      for (int i = 0; i <= 1000; i++)
      {
        ;
      }


      lcd.clear();
      lcd.print("Enter tone:");
      lcd.setCursor(0, 1);
      lcd.print("Function 2");

      while(keypressed() != 15) 
      {
        ;
      }

      temp_char = '$';

      char sequence[6];
      int s_count = 0;

      while(global_menu.cMenu() == 2) 
      {
        temp_char = keypad_read(temp_char);
        
        if (temp_char == '1' || temp_char == '2' || temp_char == '3' || temp_char == '4' || temp_char == '5' || temp_char == '6' || temp_char == '7' )
        {
          sequence[s_count] = temp_char;
          lcd.setCursor((11+s_count) ,0);
          lcd.print(sequence[s_count]);


          if (s_count >= 4) {
            
            lcd.setCursor(0, 1);
            lcd.print("               ");
            lcd.setCursor(0, 1);

            for(int i = 0; i <= 4; i++) 
            {
              temp_char = assignNote(sequence[i]);
              lcd.print(temp_char);
              if (i != 4) { lcd.print("4,"); } else { lcd.print("4"); }
              delay(10);
              while (TIMSK2 >> 1) { ; }
            }
            delay(1000);
            s_count = 0;
            lcd.clear();
            lcd.print("Enter tone:");
            lcd.setCursor(0, 1);
            lcd.print("Key 9 to return");
          } else { s_count++; }
          //temp_char = ''
        }

        if (temp_char == '9')
        {
          lcd.clear();
          lcd.print("Returning...");
          global_menu.cMenu(0);
        }

        while(keypressed() != 15) 
        {
          ;
        }

        temp_char = '$';
      }
    }


    //------------------------------------------------------------------------------------------------------
    if (global_menu.cMenu() == 3)
    { //Function 3
      TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);

      pmw_interrupts(); // Initiate Interrupt Register
      //TIMSK2 |= (1 << 1); //Turn on interrupts

      lcd.clear();
      lcd.print("Init Interrupts");
      //TIMSK2 |= (1 << 1);
      for (int i = 0; i <= 1000; i++)
      {
        ;
      }
      
      lcd.clear();
      lcd.print("1. Zap - 2. Ray");
      lcd.setCursor(0,1);
      lcd.print("3. Blast");
      temp_int = keypressed();
      int i = 0;
      int i_count = 0;
      int gap = 0;

      char temp_pressed = 'a';

      while(global_menu.cMenu() == 3)
      {
        while(temp_int != 15) { temp_int = keypressed(); delay(1); }
        

        //OCR2A = 5;
        temp_char = keypad_read(temp_char);
        temp_int = keypressed();

        lcd.clear();
        lcd.print("Reading Key");
        lcd.setCursor(0,1);
        lcd.print("'9' to return");


        if (temp_char == '1') 
        {
          TIMSK2 |= (1 << 1 | 1);
          temp_pressed = keypad_read(temp_pressed);
          global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Zap");
          while (i < zap_length)
          {
            temp_char = pgm_read_byte(&zap_data[i]);
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            delayMicroseconds(1000);
          }
          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
          delay(500);
          temp_char = 'a';
        }

        if (temp_char == '2') 
        {
          TIMSK2 |= (1 << 1 | 1);
          temp_pressed = keypad_read(temp_pressed);
          global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Ray");
          while (i < ray_length)
          {
            temp_char = pgm_read_byte(&ray_data[i]);
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            delayMicroseconds(1000);
          }
          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
          delay(500);
          temp_char = 'a';
        }

        if (temp_char == '3') 
        {
          TIMSK2 |= (1 << 1 | 1);
          temp_pressed = keypad_read(temp_pressed);
          global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Blast");
          while (i < blast_length)
          {
            temp_char = pgm_read_byte(&blast_data[i]);
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            delayMicroseconds(1000);
          }
          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
          delay(500);
          temp_char = 'a';
        }



        if (temp_char == '4') 
        {
          TIMSK2 |= (1 << 1 | 1);
          temp_pressed = temp_char;
          i_count = keypressed();
          //global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Zap");
          lcd.setCursor(0,1);
          if (gap == 0) 
          {
            lcd.print("0 second gap"); 
          } else {
            lcd.print("0.");
            lcd.print(gap);
            lcd.print(" second gap");
          }
          while (i <= zap_length && i_count != 15)
          {
            temp_pressed = keypad_read(temp_pressed);
            i_count = keypressed();
            for (int jay = 0; jay < 4000; jay++) { ; }
            temp_char = pgm_read_byte(&zap_data[i]);
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            if (i == zap_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); delay(gap*100); TIMSK2 |= (1 << 1 | 1); }
            delayMicroseconds(1000);
          }

          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
          temp_char = 'a';
        }



        if (temp_char == '5') 
        {
          TIMSK2 |= (1 << 1 | 1);
          i_count = keypressed();
          global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Ray");
          lcd.setCursor(0,1);
          if (gap == 0) 
          {
            lcd.print("0 second gap"); 
          } else {
            lcd.print("0.");
            lcd.print(gap);
            lcd.print(" second gap");
          }
          while (i <= ray_length && i_count != 15)
          {
            temp_char = pgm_read_byte(&ray_data[i]);
            i_count = keypressed();
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            if (i == ray_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); delay(gap*100); TIMSK2 |= (1 << 1 | 1); }
            delayMicroseconds(1000);
          }
          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
        }


        if (temp_char == '6') 
        {
          TIMSK2 |= (1 << 1 | 1);
          i_count = keypressed();
          global_menu.icount(1);
          lcd.clear();
          lcd.print("SFX Blast");
          lcd.setCursor(0,1);
          if (gap == 0) 
          {
            lcd.print("0 second gap"); 
          } else {
            lcd.print("0.");
            lcd.print(gap);
            lcd.print(" second gap");
          }
          while (i <= blast_length && i_count != 15)
          {
            temp_char = pgm_read_byte(&blast_data[i]);
            i_count = keypressed();
            temp_int = (int)temp_char;
            OCR2A = temp_int;
            //lcd.clear();
            //lcd.print(i);
            i++;
            if (i == blast_length) { i = 0; TIMSK2 &= ~(1 | 1 << 1 | 1 << 2); delay(gap*100); TIMSK2 |= (1 << 1 | 1); }
            delayMicroseconds(1000);
          }
          i = 0;
          TIMSK2 &= ~(1 | 1 << 1 | 1 << 2);
        }

        if (temp_char == '9')
        {
          lcd.clear();
          lcd.print("Returning...");
          global_menu.cMenu(0);
        }

        if (temp_char == '*') {
          if (gap > 0) { gap--; }
          lcd.clear();
          if (gap == 0) 
          {
            lcd.print("0 second gap"); 
          } else {
            lcd.print("0.");
            lcd.print(gap);
            lcd.print(" second gap");
          }

          i_count = keypressed();
          while(i_count != 15) { i_count = keypressed(); delay(1); }
          delay(500);
          temp_char = 'a';

        }

        if (temp_char == '#') {
          if (gap < 9) { gap++; }

          lcd.clear();
          lcd.print("0.");
          lcd.print(gap);
          lcd.print(" second gap");
          i_count = keypressed();
          while(i_count != 15) { i_count = keypressed(); delay(1); }
          delay(500);
          temp_char = 'a';
        }
        
        delay(100);
      }
    }
    
    if (global_menu.cMenu() == 4)
    {
      temp_char = keypad_read(temp_char);
      temp_int = keypressed();
      lcd.clear();
      lcd.print(temp_char);
      lcd.setCursor(0,1);
      lcd.print(temp_int);
      delay(100);
    }

  }
  return 1;
}

/*
Code used to measure voltage, current, and power using and LCD Screen
and LEDs

Done as Part of Class Project for ECEN 459
Aaron Colchado
*/

// include the library code for LCD:
#include <LiquidCrystal.h>


// initialize the library by associating any needed LED and LCD interface pins
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, VOL_PIN = A5, buttonPin = 8, LED1 = 1, LED2 = 6, LED3 = 7, LED4 = 9, LED5 = 10;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
//initializes push button value
int buttonState = 0;

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  Serial.begin( 9600 );
  //Sets up the push button as an input
  pinMode(buttonPin, INPUT);
  //Sets LEDs as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
}

void loop() {
  //Used to set output to LCD as char values
  char Mode;
  //Reads the voltage input and sets the max input value
  float volt = analogRead(A5)*5.5/1023;
  float current = volt/18.9;            //  Current = Voltage / (R1+R2) 
  float power = volt * current;
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  //Uses the button as an input to determine whether Power or Voltage and Current get shown.
  if (buttonState == LOW){
  // set the cursor to column 0, line 1
  lcd.setCursor(0,0);
  lcd.print("Voltage: ");
  lcd.print(volt);
  lcd.print("V  ");
  //Moves Cursor to write on secod line of LCD
  lcd.setCursor(0, 1);
  lcd.print("Current: ");
  lcd.print(current);
  lcd.print("A  ");
  //Calls LEDLevel() function
  LEDLevel();
  }

  else{
  lcd.setCursor(0,0);
  lcd.print("Power: ");
  lcd.print(power);
  lcd.print("W     ");  
  lcd.setCursor(0, 1);
  //Uses whitespace to overwrite the characters from the other display option.
  lcd.print("               ");
  LEDLevel();
  }
}

/*
LEDLevel() reads in voltage input and determines which LED to light up depending on the voltage measured
*/
void LEDLevel(){
  float volt = analogRead(A5)*5.5/1023;
  if(volt < 1.5){ 
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
  }

  else if(volt < 2.5 && volt >= 1.5 ){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
    }

  else if(volt < 3.5 && volt >= 2.5 ){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, LOW);
  digitalWrite(LED5, LOW);
    }

  else if(volt < 4.5 && volt >= 3.5 ){
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, LOW);
    }

  else{
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, HIGH);
  digitalWrite(LED3, HIGH);
  digitalWrite(LED4, HIGH);
  digitalWrite(LED5, HIGH);
    }
}

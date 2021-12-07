/*
Code used to control solar panel movement using two arduino unos for 
vertical and horizontal movent using input values from LDR sensors.

Done as part of class project for ECEN 459
Aaron Colchado
*/

// Adds Servo library to use with arduino
#include <Servo.h>
//defining Servo Start postion and max and min position
Servo servohori;
int servoh = 0;
int servohLimitHigh = 180;
int servohLimitLow = 0;

Servo servoverti; 
int servov = 0; 
int servovLimitHigh = 180;
int servovLimitLow = 0;

//Assigning LDRs to input pins
int ldrtopl = 0; //top left LDR Blue/Purple
int ldrtopr = 1; //top right LDR Black/White
int ldrbotl = 3; // bottom left LDR Red/Orange
int ldrbotr = 2; // bottom right LDR Green/Yellow

 void setup () 
 {
  //Sets up output pins to control servo motors and sets them to zero position
  servohori.attach(6);
  servohori.write(0);
  servoverti.attach(5);
  servoverti.write(0);
  delay(500);
 }

void loop()
{
 
  //Reads in the LDR values from each sensor
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // calculates average light value of each perimeter of Solar Panel
  int avgtop = (topl + topr) / 2; //average of top LDRs
  int avgbot = (botl + botr) / 2; //average of bottom LDRs
  int avgleft = (topl + botl) / 2; //average of left LDRs
  int avgright = (topr + botr) / 2; //average of right LDRs

/*
Vertical Movement of Motor
*/

  //Sets threshhold value for difference between sides before deciding movement 
  if ((avgtop - avgbot) > 20)
  {
    //Moves Servo motor 1 degree up per refresh rate while in loop
    servoverti.write(servov +1);
    
    //Sets condition to keep servo motor at maximum allowed limit
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
  }
  else if ((avgbot - avgtop) > 20)
  {
    servoverti.write(servov -1);
    
    if (servov < servovLimitLow)
    {
      servov = servovLimitLow;
    }
  }
  //Maintains motor position if average falls below threshhold
  else 
  {
    servoverti.write(servov);
  }

/*
Horizontal Movement of Motor
*/
 
  if ((avgleft - avgright) > 20)
    {
      servohori.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
  }
  
  else if ((avgright - avgleft) > 20)
  {
    servohori.write(servoh -1);
    if (servoh < servohLimitLow)
     {
      servoh = servohLimitLow;
     }
  }
  
  else 
  {
    servohori.write(servoh);
  }
}

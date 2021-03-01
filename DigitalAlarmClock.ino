/*
 * THE LIBRARIES DS3231.h AND LiquidCrystal_I2C.h
 * ARE DEVELOPED BY 3RD PARTIES.
 * 
 * I DO NOT OWN ANY RIGHTS TO EITHER OF THEM EXCEPT
 * WHAT IS ALLOWED BY THEIR RESPECTIVE LICENSES.
 * 
 * I HAVE INCLUDED THEM IN THE GIT REPO BECAUSE OLD LINKS
 * SOMETIMES GO MISSING.
 * 
 * THE AUTHOR OF DS3231 LIBRARY HAS INCLUDED AN AMAZING
 * PDF MANUAL. IT IS INCLUDED WITH THE .ZIP
 * FILE, DO HAVE A LOOK AT IT IF YOU WISH TO MAKE CHANGES.
 * 
 * IT DOESN'T LOOK AS IF DS3231 THE LIBRARY IS MAINTAINED
 * SO ANY POTENTIAL BUGS MAY NOT BE FIXED IN FUTURE.
 * 
 * REPORT ISSUES OR REQUIREMENTS AT https://github.com/aashish-joshi/DuinoClock/issues
 * 
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>      // SOURCE https://github.com/johnrickman/LiquidCrystal_I2C
#include <DS3231.h>                 // SOURCE http://www.rinkydinkelectronics.com/library.php?id=73

DS3231 rtc(SDA, SCL);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int temp;

// buzzer pin number
const int buzzer = 9;

/* Pin number for vibration motor
 * 
 * COMMENT THE FOLLOWING LINE OR REMOVE IT
 * IF YOU DO NOT HAVE A VIBRATION MOTOR
 */
const int vibration = 10;


void setup()
{
  Serial.begin(9600);
  rtc.begin();                  // initialize the DS3231
  
  lcd.init();                   // initialize the LCD 
  
  lcd.backlight();              // TURN THE BACKLIGHT ON

  /*
   * PRINT STATIC TEXT THAT NEVER CHANGES
   */
  lcd.setCursor(14,1);
  lcd.print((char)223);       // degree character
  lcd.setCursor(15,1);
  lcd.print("C");             // print C for celcius

  pinMode(buzzer, OUTPUT);    // Set buzzer - pin 9 as an output
  
  /*
   * Set pin 10 as output for vibration motor.
   * 
   * COMMENT THE FOLLOWING LINE WITH A // OR REMOVE IT
   * IF YOU DO NOT HAVE A VIBRATION MOTOR
   */
  pinMode(vibration,OUTPUT);

}



void loop()
{
  // PRINT THE CURRENT DATE
  lcd.setCursor(1,0);

  /*
   * FORMAT_LONG -> print the full year
   * FORMAT_LITTLEENDIAN -> day-month-year format
   * 
   * Interesting article about the little endian date format :-) https://bit.ly/2PkQSJM
   * 
   * The date separator used is '/' feel free to change to '-' or something else.
   * 
   */
  lcd.print(rtc.getDateStr(FORMAT_LONG,FORMAT_LITTLEENDIAN,'/'));   // 
  
  //PRINT THE DAY OF WEEK IN SHORT FORM
  lcd.setCursor(12,0);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  // PRINT THE CURRENT TIME IN HH:MM:SS FORMAT
  char *currTime = rtc.getTimeStr();
  lcd.setCursor(2,1);
  lcd.print(currTime);

  // Sound the buzzer 2 times 
  // if the hour has just changed
  if(currTime[3] == '0' && currTime[4] == '0' && currTime[6] == '0' && currTime[7] == '0'){

    // turn the buzzer and vibration
    // on for 250ms(1/4 second)
    digitalWrite(buzzer,HIGH);
    digitalWrite(vibration,HIGH);   // comment this line if you don't have a vibration motor
    delay(250);
    
    //turn off the buzzer for 250ms
    digitalWrite(buzzer,LOW);
    delay(250);

    // turn on the buzzer once again for 250ms
    digitalWrite(buzzer,HIGH);
    delay(250);

    //Finally turn off the buzzer
    //and the vibration motor
    digitalWrite(buzzer,LOW);
    digitalWrite(vibration,LOW);
  }
  else if (currTime[3] == '3' && currTime[4] == '0' && currTime[6] == '0' && currTime[7] == '0'){

    // if it is 30 minutes past the hour
    // just beep once
    digitalWrite(buzzer,HIGH);
    digitalWrite(vibration,HIGH);
    
    delay(500);                     //wait for 500ms
    
    digitalWrite(buzzer,LOW);
    digitalWrite(vibration,LOW);
  }

  // PRINT THE CURRENT TEMPERATURE in C
  lcd.setCursor(12,1);
  temp = rtc.getTemp();
  lcd.print(temp);

  // WAIT 1 SEC BEFORE REFRESHING
  delay(1000);
}

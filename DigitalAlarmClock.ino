#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

DS3231 rtc(SDA, SCL);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int temp;

// buzzer pin number
const int buzzer = 9;

//vibration motor pin number
const int vibration = 10;

void setup()
{
  Serial.begin(9600);
  rtc.begin();    // initialize the DS3231
  
  lcd.init();                      // initialize the lcd 
  //lcd.init();
  // TURN THE BACKLIGHT ON
  lcd.backlight();

  // PRINT STATIC TEXT THAT NEVER CHANGES
  lcd.setCursor(14,1);
  lcd.print((char)223); // degree character
  lcd.setCursor(15,1);
  lcd.print("C"); // print C for celcius

  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
  pinMode(vibration,OUTPUT); // Set pin 10 as output for vibration motor.

}


void loop()
{
  // PRINT THE CURRENT DATE
  lcd.setCursor(1,0);
  lcd.print(rtc.getDateStr(FORMAT_LONG,FORMAT_LITTLEENDIAN,'/'));

  //PRINT THE DAY OF WEEK IN SHORT FORM
  lcd.setCursor(12,0);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  // PRINT THE CURRENT TIME IN HH:MM:SS FORMAT
  char *currTime = rtc.getTimeStr();

  // Sound the buzzer 2 times 
  // if the hour has just changed
  if(currTime[3] == '0' && currTime[4] == '0' && currTime[6] == '0' && currTime[7] == '0'){

    //beep and vibrate
    digitalWrite(buzzer,HIGH);
    digitalWrite(vibration,HIGH);
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
    digitalWrite(buzzer,HIGH);
    digitalWrite(vibration,HIGH);
    delay(250);//wait for 1ms
    digitalWrite(buzzer,LOW);
    digitalWrite(vibration,LOW);
  }
  
  lcd.setCursor(2,1);
  lcd.print(currTime);

  // PRINT THE CURRENT TEMPERATURE
  lcd.setCursor(12,1);
  temp = rtc.getTemp();
  lcd.print(temp);

  // WAIT 1 SEC BEFORE REFRESHING
  delay(1000);
}

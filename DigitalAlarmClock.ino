#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <DS3231.h>

DS3231 rtc(SDA, SCL);

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

int temp;

void setup()
{
  Serial.begin(9600);
  rtc.begin();    // initialize the DS3231
  
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // TURN THE BACKLIGHT ON
  lcd.backlight();

  // PRINT STATIC TEXT THAT NEVER CHANGES
  lcd.setCursor(14,1);
  lcd.print((char)223);
  lcd.setCursor(15,1);
  lcd.print("C");
}


void loop()
{
  // PRINT THE CURRENT DATE
  lcd.setCursor(1,0);
  lcd.print(rtc.getDateStr(FORMAT_LONG,FORMAT_LITTLEENDIAN,'-'));

  //PRINT THE DAY OF WEEK IN SHORT FORM
  lcd.setCursor(12,0);
  lcd.print(rtc.getDOWStr(FORMAT_SHORT));

  // PRINT THE CURRENT TIME IN HH:MM:SS FORMAT
  lcd.setCursor(1,1);
  lcd.print(rtc.getTimeStr());

  // PRINT THE CURRENT TEMPERATURE
  lcd.setCursor(12,1);
  temp = rtc.getTemp();
  lcd.print(temp);

  // WAIT 1 SEC BEFORE REFRESHING
  delay(1000);
}


#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
SoftwareSerial RFID(2, 3); // RX and TX
int i;
void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
    lcd.print("hello, world!");
}

void loop()
{
    if (RFID.available() > 0) 
    {
        i = RFID.read();
        Serial.print(i, DEC);
        Serial.print(" ");
    }
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print

/*
 #include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);

void setup()
{
  lcd.print("hello, world!");
}

void loop() {}
 
 */
//We need code to store the tag info in an array
//LCD needs to display available spots in the array


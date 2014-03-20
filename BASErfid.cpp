
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
SoftwareSerial RFID(2, 3); // RX and TX
int i;

char inData[20]; // Allocate some space for the string
char inChar; // Where to store the character read
byte index = 0; // Index into array; where to store the character

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
    
    while(Serial.available() > 0) // Don't read unless there is data
    {
       if(index < 19) // One less than the size of the array
       {
           inChar = Serial.read(); // Read a character
           inData[index] = inChar; // Store it
           index++; // Increment where to write next
           inData[index] = '\0'; // Null terminate the string
       }
    }
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array



#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
SoftwareSerial RFID(2, 3); // RX and TX

int i;
char tag_num_array[5][90]; // Allocate some space for the string
char tag_id; // Where to store the character read
char row = 0; // Index into array; where to store the character
char column = 0;

void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
    //lcd.print("hello, world!");
}

void loop()
{
    /*if (RFID.available() > 0) 
    {
        i = RFID.read();
        Serial.print(i, DEC);
    }*/
    
    if(RFID.available() > 0) //does rfid exist?
    {
        tag_id = RFID.read();   //take the data pulled from RFID and set it to "in
        tag_num_array[row][column] = tag_id; // takes the data that was just stored, and puts it in the array
        column++;
        tag_num_array[row][column] = '\0'; // Null terminate the string
        row++; // increments to the next row in the array
        Serial.print(tag_num_array[index][index2]);   //prints out the array
    }
    
    //the adding of the array may need to be external to this read loop, otherwise it could be overwriting it. 
    
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array



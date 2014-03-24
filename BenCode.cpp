
#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
SoftwareSerial RFID(2, 3); // RX and TX
int i;

int tag_num_array[6][90]; // Allocate some space for the string
int tag_id; // Where to store the character read
byte row = 0; // Index into array; where to store the character
byte column = 0;


void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
}

void loop()
{
    
    
    if(RFID.available() > 0) //does rfid exist?
    {
        tag_id = RFID.read();   //take the data pulled from RFID and set it to "in
        tag_num_array[row][column] = tag_id; // takes the data that was just stored, and puts it in the array
        row++; // increments to the next row in the array
       column++;
        tag_num_array[row][column] = '\0'; // Null terminate the string
       // Serial.print(tag_num_array[row][column]);   //prints out the array
       Serial.print (column);
    }
    

}




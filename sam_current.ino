// 3/23/14 To Do next:
// Print out full list of tags in the array?
// Start working on maths for checking if tag is currently in the array



#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 10, 5, 4, 3, 2);
SoftwareSerial RFID(2, 3); // RX and TX

//int i = 0;
int bytesRead = 0;

char tag_id; // Where to store the character read
String id_string = "";
String id_array[5];
byte index = 0; // Index into array; where to store the character
String previous_id_array[5];

int space_left = 5;

void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
    //lcd.print("hello, world!");
    Serial.println("Ready!");
}

void loop()
{
    /*
    if (RFID.available() > 0) 
    {
        i = RFID.read();
        //Serial.print(i, DEC);
        Serial.print(i);
    }
    */
    if(RFID.available() > 0) //does rfid exist?
    {
      tag_id = RFID.read(); //Reads character, puts into tag_id
      bytesRead ++; // increments the number of total characters read
      id_string += tag_id; //adds each character (ultimately, the whole tag) to id_string
      //Serial.print(tag_id);
      
      //check for the end of the RFID
      if (bytesRead >= 14) //if the number of bytes is greater or equal to 14, then
      {
        //Serial.println(" ");
        //Serial.println(id_string);
        
        Serial.println(" "); // prints a space
        id_array[index] = id_string; // adds string to the array, to the "index" position (default 0)
        
        Serial.println(id_array[index]); // print the array item
        Serial.println("Finished Reading ID."); //prints out this on a line
        index++;
        
        if (id_array[index] == previous_id_array[index])
        {
            space_left++;
        }
        else
        {
            space_left--;
        }  
                
                
        Serial.print("There are "); //start printing the result
        Serial.print(space_left); //then how many spaces
        Serial.print(" spaces left."); //words
        Serial.println(" "); //spaces
        
        bytesRead = 0; // reset variable to zero so it can read again
        id_string = ""; //clear out the string
        id_array[index] = previous_id_array[index];
        
      }
      
        //tag_id = RFID.read();   //take the data pulled from RFID and set it to "in
        //tag_num_array[index] = tag_id; // takes the data that was just stored, and puts it in the array
        //index++; // increments to the next row in the array
        //tag_num_array[index] = '\0'; // Null terminate the string
        //Serial.print(tag_id);
        //Serial.print(" ");
        //Serial.print(index);
        
       
        //Serial.print(tag_num_array);   //prints out the array
        //Serial.print(tag_id);
        //Serial.print(index);
    }
    
    //the adding of the array may need to be external to this read loop, otherwise it could be overwriting it. 
    

}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array


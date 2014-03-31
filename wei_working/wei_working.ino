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
//char id_string[15];
String id_array[5];
int id_marker[5];
byte index = 0; // Index into array; where to store the character
int no_match = 0;
//byte index2 

int space_left = 5;

void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
    //lcd.print("hello, world!");
    
    for (int i = 0; i < 5; i++)
       id_marker[i] = 0;
    
    Serial.println("Ready!");
}

void loop()
{
    int i;
    bytesRead = 0;
    
    while (RFID.available() <= 0);
    
    if(RFID.available() > 0) //does rfid exist?
    {
      i = 0;
      
      while (i < 14)
      {
      
      tag_id = RFID.read(); //Reads character, puts into tag_id
      
      if (tag_id == '-1')
           continue;
      
      //id_string[bytesRead] = tag_id;
      id_string = String(id_string + tag_id);
      
      bytesRead ++; // increments the number of total characters read
      
        Serial.print("Read:  "); //prints out this on a line
        Serial.print(tag_id);
        Serial.print("\nid_string is now "); //start printing the result
        Serial.print(id_string); //then how many spaces
           i++; 
      }
      //id_string[bytesRead] = '\0';

       Serial.print("\nid_string is now "); //start printing the result
        Serial.print(id_string); //then how many spaces

      
      //id_string += tag_id; //adds each character (ultimately, the whole tag) to id_string
      //id_array[index] = id_string;
      //id_marker[index]++;
      //index++;
      
      //check for the end of the RFID
      //if (bytesRead >= 14) //if the number of bytes is greater or equal to 14, then
      //{
        //Serial.println(" ");
        //Serial.println(id_string);
        
        
        
        for(int i=0; i<5; i++)
        {
              Serial.print("\nid_array["); //prints out this on a line
              Serial.print(i);
              Serial.print("] = ");
              Serial.print(id_array[i]);
              Serial.print("\nid_string is "); //start printing the result
              Serial.print(id_string); //then how many spaces
              
           if(id_string == id_array[i])
           {
             Serial.println("Match");
             
              if (id_marker[i] == 1);
              else
              {
                space_left++;
                
                for (int j = i; j < 4; j++)
                {
                   id_string[j] = id_string[j + 1];
                   id_marker[j] = id_marker[j + 1];
                }
                index--;
                space_left++;
                //id_array[i] = "";
                //i = index;
                no_match = 1;
              }
              //break;
           }

        }
        
        
         if (no_match == 0)
           {
             id_array[index] = id_string;
             id_marker[index]++;
      
             space_left--;
              // adds string to the array, to the "index" position (default 0)
             index ++; // move to the next position in the array
           }

          }
        
                
        
        Serial.println(" "); // prints a space
        Serial.println(id_array[index]); // print the array item
        Serial.println("Finished Reading ID."); //prints out this on a line
        Serial.print("There are "); //start printing the result
        Serial.print(space_left); //then how many spaces
        Serial.print(" spaces left."); //words
        Serial.println(" "); //spaces
        
        bytesRead = 0; // reset variable to zero so it can read again
        no_match = 0; 
        id_string = String(""); //clear out the string
        
        //exit(1);
 //     }
      
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array



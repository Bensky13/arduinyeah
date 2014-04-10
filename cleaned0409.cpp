#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 7, 8); //Declaring pins
SoftwareSerial RFID(2, 3); // RX and TX

//Declare Variables
char tag_id;
String id_string = "";
String id_array[5];
int id_marker[5];
int index = 0;
int no_match = 0;
int space_left = 5;

//Arduino Setup
void setup()
{
    RFID.begin(9600); //Start serial to RFID reader
    Serial.begin(9600); //Start serial to PC
    lcd.begin(16, 2); //Set rows and columns on LCD
    
    //Initial LCD Output
    lcd.clear();
    lcd.print("There are "); //start printing the result
    lcd.print(space_left); //then how many spaces
    lcd.println("  spaces left."); //words
    
    //Set Marker
    for (int i = 0; i < 5; i++)
    {
       id_marker[i] = 0;
    }
    
    Serial.println("Ready!");
     
    //Sets everything in the array equal to blank
    for(int i=0; i<5; i++)
    {
        id_array[i] = String("");
    }
  
}

//Read card, handle array, output to LCD
void loop()
{
    int i;
    while (RFID.available() <= 0); // force wait until rfid present
    
    if(RFID.available() > 0) //does rfid exist?
    {
        i = 0;
        
        while (i < 14)
        {
        
            tag_id = RFID.read(); //Reads character, puts into tag_id
            
            if (tag_id == '-1')  //Wait for scan to read
                continue;
            
            id_string = String(id_string + tag_id); //Make it a string
            
            //Internal testing, not seen by user
            Serial.print("Read:  "); 
            Serial.print(tag_id);
            Serial.print("\nid_string is now "); 
            Serial.print(id_string); 
            
            i++; //counts up until 14
        }
            
        //TESTING OUTPUT
        Serial.print("\nid_string is now ");
        Serial.print(id_string);
        
        
        for(int index=0; index<5; index++)  //first we check to see if there are any current matches
        {
        
            if(id_string == id_array[index]) //if the id matches another tag in the array
            {
                Serial.println("Match"); //print that it matches.
                id_array[index] = String("");    //set the array location of the removed tag to blank
                  
                index--;  //this might actually only subtract the last place, and not the proper location
                space_left++;
                no_match = 1;
            }
        }
            
        if (no_match == 0)
        {
            for (index = 0; index < 5; index++)
            if (id_array[index] == String(""))   //if the array location is blank, move on
            {
                break;
            }
            
            if (index == 5)  //if we're at the 5th spot
            {
                Serial.println("The lot is full");
            }
            else
            {
                //this needs to be able to detect black values
                id_array[index] = id_string;
                id_marker[index]++;
                space_left--;
            }
        }
    
    }
    
    //Internal testing output, not seen by user
    Serial.println(" "); // prints a space
    Serial.println(id_array[index]); // print the array item
    Serial.println("Finished Reading ID."); //prints out this on a line
    Serial.print("There are "); //start printing the result
    Serial.print(space_left); //then how many spaces
    Serial.println(" spaces left."); //words
    
    //LCD output, seen by user
    lcd.clear();
    lcd.print("There are "); //start printing the result
    lcd.print(space_left); //then how many spaces
    lcd.println("  spaces left."); //words
    
    //Testing output, display array, not seen by user
    for(int i=0; i<5; i++)
    {
          Serial.print("\nid_array[");
          Serial.print(i);
          Serial.print("] = ");
          Serial.print(id_array[i]);
    }
    //Reset Variables
    no_match = 0; 
    id_string = String(""); //clear out the string
}
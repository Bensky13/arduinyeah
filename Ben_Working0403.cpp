#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
SoftwareSerial RFID(2, 3); // RX and TX

char tag_id;
String id_string = "";
String id_array[5];
int id_marker[5];
int bytesRead = 0;
int index = 0;
int no_match = 0;
int space_left = 5;

void setup()
{
    RFID.begin(9600); // start serial to RFID reader
    Serial.begin(9600); // start serial to PC
    //lcd.begin(16, 2);
    //lcd.print("Ready!");
    
    for (int i = 0; i < 5; i++)
       id_marker[i] = 0;
    
    Serial.println("Ready!");
     
  
 
  
}

void loop()
{
    int i;
    bytesRead = 0; //I think this is now not needed, haven't tested yet
    
    while (RFID.available() <= 0);
    
    if(RFID.available() > 0) //does rfid exist?
    {
      i = 0;
      
      while (i < 14)
      {
      
        tag_id = RFID.read(); //Reads character, puts into tag_id
      
      
        if (tag_id == '-1')  //Wait for scan to read
           continue;
      
        id_string = String(id_string + tag_id); //Make it a string
      
        bytesRead ++;
      
        //TESTING OUTPUT
        Serial.print("Read:  "); 
        Serial.print(tag_id);
        Serial.print("\nid_string is now "); 
        Serial.print(id_string); 
        
        i++; 
      }
      
      
      /*
      //TESTING OUTPUT
      Serial.print("\nid_string is now ");
      Serial.print(id_string);
      
      //Commenting this out, as it seems redundant to above code.
      
      */

      
      //id_string += tag_id; //adds each character (ultimately, the whole tag) to id_string
      //id_array[index] = id_string;
      //id_marker[index]++;
      //index++;   
        
        
        for(int i=0; i<5; i++)
        {
              //TEST OUTPUT: DISPLAY ARRAY
              Serial.print("\nid_array[");
              Serial.print(i);
              Serial.print("] = ");
              Serial.print(id_array[i]);
              Serial.print("\nid_string is ");
              Serial.print(id_string);
              
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
                  no_match = 1;
                }
              
           }

        }//End of for loop
        
        
         if (no_match == 0)
         {
             id_array[index] = id_string;
             id_marker[index]++;
      
             space_left--;
             index ++;
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
      
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array

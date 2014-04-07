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


//It's always overwriting the second value in the array


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
        
        //For some reason, getting rid of this makes the tag not read correctly 
        Serial.print("Read:  "); 
        Serial.print(tag_id);
        Serial.print("\nid_string is now "); 
        Serial.print(id_string); 
        
        i++; 
      }
      
      
      
      //TESTING OUTPUT
      Serial.print("\nid_string is now ");
      Serial.print(id_string);
      
      
      
      

      
      //id_string += tag_id; //adds each character (ultimately, the whole tag) to id_string
      //id_array[index] = id_string;
      //id_marker[index]++;
      //index++;   
        
        
        for(int i=0; i<5; i++)
        {
            
        
        /*
            //Moved to the land down under
              //TEST OUTPUT: DISPLAY ARRAY
              Serial.print("\nid_array[");
              Serial.print(i);
              Serial.print("] = ");
              Serial.print(id_array[i]);
              Serial.print("\nid_string is ");
              Serial.print(id_string);
            //This should ultimately be after the final read/print action so we can get relevant data
            
            */
              
           if(id_string == id_array[i]) //if the id matches something in the array at location "i"
           {
               Serial.println("Match"); //print that it matches.
               id_array[i] = "";    //set the array location of the removed tag to blank
               
               
             
               if (id_marker[i] == 1);  //if the id marker is equal to one
               //else //Removing this else because I dont think it makes sense. 
               {
                 // space_left++; //this isnt properly increasing the spaces left
                  //Commented out space left above because theres also one below.
                  
                  //where does it get removed from the array if its a dup?
                  
                /* Removed on 4/6 because I cant detect why this is necessary. 
                  for (int j = i; j < 4; j++)   //what purpose does j serve? Increments the search?
                  {
                     id_string[j] = id_string[j + 1]; 
                     id_marker[j] = id_marker[j + 1];
                     Serial.println(id_marker[i]);  //test print for the current marker. 
                  }
                  
                  */
                  
                  index--;  //this might actually only subtract the last place, and not the proper location
                  space_left++;
                  no_match = 1;
                }
              
           }

        }//End of for loop
        
        
        
        
        
         if (no_match == 0)
         {
            
            if (id_array[index] != "");   //if the array location is not blank, then
        {
            index ++;   //increment to the next spot
        }
        
        if (i == 5);  //if we're at the 5th spot
        {
            i == 0; //start back at zero
        }
            
             //this needs to be able to detect black values
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
        
        for(int i=0; i<5; i++)
        {
            
            
            
              //TEST OUTPUT: DISPLAY ARRAY. I put this here because its more accurate
              Serial.print("\nid_array[");
              Serial.print(i);
              Serial.print("] = ");
              Serial.print(id_array[i]);
              //Serial.print("\nid_string is ");
              //Serial.print(id_string);
            
        }
        
        bytesRead = 0; // reset variable to zero so it can read again
        no_match = 0; 
        id_string = String(""); //clear out the string
      
}


//we need general output code for the LCD. Once we have this, we can put whatever we want in it. lcd.print
//We need code to store the tag info in an array
//LCD needs to display available spots in the array

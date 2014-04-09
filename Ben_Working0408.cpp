#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
LiquidCrystal lcd(12, 11, 5, 4, 7, 8); //Testing code for pin switch
SoftwareSerial RFID(2, 3); // RX and TX
//SoftwareSerial RFID(8, 9); // Testing code for pin switch

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
    lcd.begin(16, 2);
    //lcd output
        lcd.clear();
        lcd.print("There are "); //start printing the result
        lcd.print(space_left); //then how many spaces
        lcd.print("  spaces left."); //words
        lcd.println(" "); //spaces
    
    for (int i = 0; i < 5; i++)
    {
       id_marker[i] = 0;
    }
    
    Serial.println("Ready!");
     
  //sets everything in the array equal to blank
 for(int i=0; i<5; i++)
        {
            id_array[i] = "";
        }
  
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
        
        //For some reason, getting rid of this makes the tag not read correctly 
        Serial.print("Read:  "); 
        Serial.print(tag_id);
        Serial.print("\nid_string is now "); 
        Serial.print(id_string); 
        
        i++; //counts up unil 14
      }
        
      //TESTING OUTPUT
      Serial.print("\nid_string is now ");
      Serial.print(id_string);
        
        
        for(int i=0; i<5; i++)  //first we check to see if there are any current matches
        {
              
           if(id_string == id_array[i]) //if the id matches something in the array at location "i"
           {
               Serial.println("Match"); //print that it matches.
               id_array[i] = "";    //set the array location of the removed tag to blank
               
               
             
               if (id_marker[i] == 1);  //if the id marker is equal to one
               //else //Removing this else because I dont think it makes sense. 
               {
                 // space_left++; //this isnt properly increasing the spaces left
                  //Commented out space left above because theres also one below.
                  
                  
                // not sure if this is necessary 
                  for (int j = i; j < 4; j++)   //what purpose does j serve? Increments the search?
                  {
                     id_string[j] = id_string[j + 1]; 
                     id_marker[j] = id_marker[j + 1];
                     Serial.println(id_marker[i]);  //test print for the current marker. 
                  }
                  
                  
                  
                  index--;  //this might actually only subtract the last place, and not the proper location
                  space_left++;
                  no_match = 1;
                }
              
           }

        }//End of for loop
        
        //I added the ifs below to attempt to refine the location of the write location in the array. they dont work completely
        if (no_match == 0)
        {
            if (id_array[index] != "");   //if the array location is not blank, then
            {
                index ++;   //increment to the next spot
            }
        
            if (i == 5);  //if we're at the 5th spot
            {
                i = 0; //start back at zero
            }
             //this needs to be able to detect black values
             id_array[index] = id_string;
             id_marker[index]++;
             space_left--;  
        }

    }
        
        Serial.println(" "); // prints a space
        Serial.println(id_array[index]); // print the array item
        Serial.println("Finished Reading ID."); //prints out this on a line
        Serial.print("There are "); //start printing the result
        Serial.print(space_left); //then how many spaces
        Serial.print(" spaces left."); //words
        Serial.println(" "); //spaces
        
        //lcd output
        lcd.clear();
        lcd.print("There are "); //start printing the result
        lcd.print(space_left); //then how many spaces
        lcd.print("  spaces left."); //words
        lcd.println(" "); //spaces
        
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
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 7, 8); //Declaring pins

//Declare Variables
int temperaturePin = 0; 
int photocellPin = 1;    
int photocellReading;

//Initialize Serial
void setup()
{
  Serial.begin(9600); 
}

//Read Temperature and Light Sensor
void loop()
{
    int reading = analogRead(temperaturePin);  
    float voltage = reading * 5.0;
    voltage /= 1024.0; 
 
    float temperatureC = (voltage - 0.5) * 100 ;
    
    Serial.print(temperatureC); Serial.println(" degrees C");
    
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    Serial.print(temperatureF); Serial.println(" degrees F");
 
    photocellReading = analogRead(photocellPin);  
    Serial.print("Light Reading = ");
    Serial.print(photocellReading);
    
    lcd.clear();
    lcd.print("Temperature:");
    lcd.print(temperatureF); lcd.print(" F");
 
    if (photocellReading < 400)
    {
        lcd.print(" Night");
    }
    else if (photocellReading < 650)
    {
        lcd.print(" Overcast");
    }
    else if (photocellReading < 800)
    {
        lcd.print(" Partly Cloudy"); 
    }
    else
    {
        lcd.print(" Sunny");
    }
    
    delay(1000);
}

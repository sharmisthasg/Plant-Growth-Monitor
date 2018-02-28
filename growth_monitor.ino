// Importing the dht and LedControl libraries
#include <dht.h>
#include <LedControl.h>

// Defining the pins of the Arduino
int DIN = 7;
int CS =  6;
int CLK = 5;

// Defining the LED Matrix

byte y1[8]={0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte y2[8]={0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00};
byte y3[8]={0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00};
byte y4[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00};
byte y5[8]={0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte y6[8]={0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
byte y7[8]={0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00};
byte y8[8]={0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00};
byte y9[8]={0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00};
byte y10[8]={0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00};
byte y11[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00};
byte y12[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00};


LedControl lc=LedControl(DIN,CLK,CS,0);
dht DHT; 

#define DHT11_PIN 2 
int ppm; 
int LDR = 1;
int LDRValue = 0;
int y;

void setup()
{ 
 Serial.begin(9600); 
 for (int i = 10; i <= 12; i++) 
 {
    pinMode(i, OUTPUT);
 }

 for (int i = 10; i <= 12; i++) 
 {
    digitalWrite(i, LOW);
 }

 lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
 lc.setIntensity(0,15);      // Set the brightness to maximum value
 lc.clearDisplay(0);         // and clear the display
} 

"""
This function prints the values of the factors i.e humidity, temperature, CO2 level and light in the considered sensors

"""
void serialPrint(char *str, int factor, int port, int voltage, int byte, int delayTime, 
                int port2, int voltage2, int delayTime2)
{
    Serial.println(str); 
    Serial.print (factor); 
    Serial.println();
    digitalWrite(port,voltage);
    printByte(byte);
    delay(delayTime);
    digitalWrite(port2,voltage2);
    delay(delayTime2);
}


"""
This function checks for the status of the factors in the considered sensors

"""

void loop() 
{ 
  int chk=DHT.read11(DHT11_PIN);
  
  // This block of code checks for the humidity requirements using a DHT11 sensor
  Serial.println("Humidity: ") ; 
  if (DHT.humidity >60)
    serialPrint ("High: ", DHT.humidity, 12, HIGH, y6, 1000, 12, LOW, 500);

  else if (DHT.humidity <60) 
    serialPrint ("Low: ", DHT.humidity, 10, HIGH, y1, 1000, 10, LOW, 500);

  else
    serialPrint ("Normal: ", DHT.humidity, 11, HIGH, y5, 1000, 11, LOW, 500);


  // This block of code checks for the temperature requirements using the same DHT11 sensor
  Serial.println("Temperature: ") ; 
  if (DHT.temperature >37.8)
    serialPrint ("High: ", DHT.temperature, 12, HIGH, y8, 1000, 12, LOW, 500);

  else if (DHT.temperature<12.8)
    serialPrint ("Low: ", DHT.temperature, 10, HIGH, y7, 1000, 10, LOW, 500); 

  else
    serialPrint ("Normal: ", DHT.temperature, 11, HIGH, y2, 1000, 11, LOW, 500); 

  // This block of code checks for the carbon dioxide requirements using a MQ135 sensor
  ppm = analogRead(0);
  Serial.println("Carbon Dioxide: ");
  if (ppm >120) 
    serialPrint ("High: ", ppm, 12, HIGH, y3, 1000, 12, LOW, 500);

  else if (ppm<80) 
    serialPrint ("Low: ", ppm, 10, HIGH, y9, 1000, 10, LOW, 500);

  else 
    serialPrint ("Normal: ", ppm, 11, HIGH, y10, 1000, 11, LOW, 500);

  """
  This block of code checks for the light requirements using an LDR

  """

  LDRValue = analogRead(LDR);
  Serial.println("Light Intensity: ");
  if (LDRValue >850) 
    serialPrint ("High: ", LDRValue, 12, HIGH, y12, 1000, 12, LOW, 500);

  else if (LDRValue<500) 
    serialPrint ("Low: ", LDRValue, 10, HIGH, y11, 1000, 10, LOW, 500)

  else 
    serialPrint ("Normal: ", LDRValue, 11, HIGH, y4, 1000, 11, LOW, 500)
    
  delay(2000);
}

"""
This function maps the observed values to the LED matrix

"""

void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

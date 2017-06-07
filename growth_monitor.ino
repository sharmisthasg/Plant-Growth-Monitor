#include <dht.h>
#include <LedControl.h>

int DIN = 7;
int CS =  6;
int CLK = 5;

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
void loop() 
{ 
  int chk=DHT.read11(DHT11_PIN);
  Serial.println("Humidity: ") ; 
  if (DHT.humidity >60) 
  {
    Serial.println("High: "); 
    Serial.print (DHT.humidity); 
    Serial.print(" %");
    Serial.println();
    digitalWrite(12,HIGH);
      printByte(y6);
    delay(1000);
    digitalWrite(12,LOW);
    delay(500);
  
    
  }
  else if (DHT.humidity <60) 
  {
    Serial.println("Low: "); 
    Serial.print (DHT.humidity); 
    Serial.print(" %");
    Serial.println();
    digitalWrite(10,HIGH);
    printByte(y1);
    delay(1000);
    digitalWrite(10,LOW);
    delay(500);
    
  }
  else 
  {
    Serial.println("Normal: "); 
    Serial.print (DHT.humidity); 
    Serial.print(" %");
    Serial.println();
    digitalWrite(11,HIGH);
    printByte(y5);
    delay(1000);
    digitalWrite(11,LOW);
    delay(500);
    
  }
  Serial.println("Temperature: ") ; 
  if (DHT.temperature >37.8) 
  {
    Serial.println("High: "); 
    Serial.print (DHT.temperature); 
    Serial.print(" degree celsius");
    Serial.println();
    digitalWrite(12,HIGH);
     printByte(y8);
    delay(1000);
    digitalWrite(12,LOW);
    delay(500);
  }
  else if (DHT.temperature<12.8) 
  {
    Serial.println("Low: "); 
    Serial.print (DHT.temperature); 
    Serial.print(" degree celsius");
    Serial.println();
    digitalWrite(10,HIGH);
    printByte(y7);
  delay(1000);
    digitalWrite(10,LOW);
    delay(500);
    
  }
  else 
  {
    Serial.println("Normal: "); 
    Serial.print (DHT.temperature); 
    Serial.print(" degree celsius");
    Serial.println();
    digitalWrite(11,HIGH);
    printByte(y2);
  delay(1000);
    digitalWrite(11,LOW);
    delay(500);
    
  }
  ppm = analogRead(0);
  Serial.println("Carbon Dioxide: ");
  if (ppm >120) 
  {
    Serial.println("High: "); 
    Serial.print (ppm); 
    Serial.print(" ppm");
    Serial.println();
    digitalWrite(12,HIGH);
    printByte(y3);
  delay(1000);
    digitalWrite(12,LOW);
    delay(500);
    
  }
  else if (ppm<80) 
  {
    Serial.println("Low: "); 
    Serial.print (ppm); 
    Serial.print(" ppm");
    Serial.println();
    digitalWrite(10,HIGH);
    printByte(y9);
  delay(1000);
    digitalWrite(10,LOW);
    delay(500);
    
  }
  else 
  {
    Serial.println("Normal: "); 
    Serial.print (ppm); 
    Serial.print(" ppm");
    Serial.println();
    digitalWrite(11,HIGH);
    printByte(y10);
  delay(1000);
    digitalWrite(11,LOW);
    delay(500);
    
  }
  LDRValue = analogRead(LDR);
  
  Serial.println("Light Intensity: ");
  if (LDRValue >850) 
  {
    Serial.println("High: "); 
    Serial.print (LDRValue); 
    Serial.print(" lux");
    Serial.println();
    digitalWrite(12,HIGH);
    printByte(y12);
  delay(1000);
    digitalWrite(12,LOW);
    delay(500);
    
    
  }
  else if (LDRValue<500) 
  {
    Serial.println("Low: "); 
    Serial.print (LDRValue); 
    Serial.print(" lux");
    Serial.println();
    digitalWrite(10,HIGH);
    printByte(y11);
  delay(1000);
    digitalWrite(10,LOW);
    delay(500);
    
  }
  else 
  {
    Serial.println("Normal: "); 
    Serial.print (LDRValue); 
    Serial.print(" lux");
    Serial.println();
    digitalWrite(11,HIGH);
    printByte(y4);
  delay(1000);
    digitalWrite(11,LOW);
    delay(500);
    
    
  }
  delay(2000);
   
} 
void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}

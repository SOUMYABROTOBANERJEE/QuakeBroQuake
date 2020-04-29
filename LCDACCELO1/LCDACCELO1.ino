       
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 8, 9, 10, 11); 
const int MPU=0x68;  
double AcX,AcY,AcZ;
void setup()
{ 
  lcd.begin(16, 2);
  lcd.print("Testing LCD - IRPEL , University of Calcutta ");
  lcd.scrollDisplayLeft();
  delay(750);
  Serial.begin(57600);
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B); 
  Wire.write(0b00000000); 
  Wire.endTransmission();
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0b00000000); 
  Wire.endTransmission();
  pinMode(9,OUTPUT);
  
}
void loop()
{ analogWrite(9,16);
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);  
  Wire.endTransmission();
  Wire.requestFrom(MPU,6);
  //while(Wire.available());  
  AcX=Wire.read()<<8|Wire.read();      
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
  lcd.setCursor(0,0);
  lcd.print("Accelerometer"); 
  lcd.scrollDisplayLeft();
  //delay(1000);
  Serial.print("AcX = "); 
  Serial.println(AcX/16384);
  lcd.setCursor(0,1);
  lcd.print("X=");
  lcd.print(AcX/16384);
 Serial.print(" | AcY = "); 
  Serial.println(AcY/16384);
  lcd.setCursor(7,1);
  lcd.print("Y=");
  lcd.print(AcY/16384);
  Serial.print(" | AcZ = ");
  Serial.println(AcZ/16384);
  lcd.setCursor(14,1);
  lcd.print("Z=");
  lcd.print(AcZ);
  delay(300);
  lcd.clear();
}



#include<Wire.h>

long accelX, accelY, accelZ;
float gForceX, gForceY, gForceZ;

long gyroX, gyroY, gyroZ;
float rotX, rotY, rotZ;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  setupMPU(); //function to establish communication with the MPU which we have to define
}

void loop() {
  recordAccelRegisters();
  recordGyroRegisters();
  printData();
  delay(200);

}

void setupMPU(){
  Wire.beginTransmission(0b1101000);//I2C address of MPU (b1101000/1 for AC0 low/high)(ds9.2)   
  Wire.write(0x6B);//Accesing register 6B for power management (ds4.28)
  Wire.write(0b00000000);//setting sleep register(read datasheet of 6B) to 0
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);// I2C address of MPU
  Wire.write(0x1B);//Accessing register 1B for gyro configuration
  Wire.write(0b00000000);//Setting the gyro to full scale +/- 250deg/sec
  Wire.endTransmission();

  Wire.beginTransmission(0b1101000);// same address of MPU
  Wire.write(0x1C);//Accessing the register 1C for accelerometer configuration
  Wire.write(0b00000000);//Setting accelerometer to +/- 2g
  Wire.endTransmission();
  }

void recordAccelRegisters(){
  Wire.beginTransmission(0b1101000);//same MPU's I2C address 
  Wire.write(0x3B);//Starting register for Accel Readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);//Request Accel Registers (3B - 40)
  
    {
    accelX = Wire.read()<<8|Wire.read();//store first two bytes into x
    accelY = Wire.read()<<8|Wire.read();//store middle two bytes into y
    accelZ = Wire.read()<<8|Wire.read();//store last two bytes into z
    processAccelData();
    }  
  }

void processAccelData(){
  gForceX = accelX /16384.0;
  gForceY = accelY / 16384.0;
  gForceZ = accelZ / 16384.0;
}

void recordGyroRegisters(){
  Wire.beginTransmission(0b1101000);//I2C address of MPU
  Wire.write(0x43);//Starting registers for gyro readings
  Wire.endTransmission();
  Wire.requestFrom(0b1101000,6);//Request Gyro registers (43 - 48)

  {
    gyroX = Wire.read()<<8|Wire.read();//Store first two bytes in x
    gyroY = Wire.read()<<8|Wire.read();//Store middle two bytes in y
    gyroZ = Wire.read()<<8|Wire.read();//Store last two bytes in z  
    processGyroData();
  }
}

void processGyroData(){
  rotX = gyroX / 131.0;
  rotY = gyroY / 131.0;
  rotZ = gyroZ / 131.0;
  }

void printData() {
  /*Serial.println(gForceX);
  Serial.print("Accl");
  Serial.print(" X=");
  Serial.println(rotX);
  Serial.print(" Y=");
  Serial.print(rotY);
  Serial.print(" Z=");
  Serial.print(rotZ);*/
  Serial.println(" Accel (g)");
  Serial.print(" X=");
  Serial.println(gForceX);
  Serial.print(" Y=");
  Serial.println(gForceY);
  Serial.print(" Z=");
  Serial.println(gForceZ);
  }


// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// MXC6232xM
// This code is designed to work with the H3LIS331DL_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Accelorometer?sku=MXC6232xM_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// MXC6232xM I2C address is 0x10(16)
#define Addr 0x10

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise Serial Communication, set baud rate = 9600
  Serial.begin(9600);

  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select Internal Control register
  // Power ON, Self-test OFF, Bandgap test normal
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  delay(300);
}

void loop()
{
  unsigned int data[5];
  
  // Start I2C Transmission
  Wire.beginTransmission(Addr);
  // Select data register
  Wire.write(0x00);
  // Stop I2C Transmission
  Wire.endTransmission();
  
  // Request 5 bytes of data from the device
  Wire.requestFrom(Addr, 5);
  
  // Read 5 bytes of data
  // status, xAccl msb, xAccl lsb, yAccl msb, yAccl lsb
  if(Wire.available() == 5) 
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
    data[4] = Wire.read();
  }

  // Convert the data
  int xAccl = (((data[1] & 0x0F) * 256) + data[2]);
  if (xAccl > 2047)
  {
    xAccl -= 4096;
  }
  
  int yAccl = (((data[3] & 0x0F) * 256) + data[4]);
  if (yAccl > 2047)
  {
    yAccl -= 4096;
  }
  
  // Output data to serial monitor
  Serial.print("Acceleration in X-Axis : ");
  Serial.println(xAccl);
  Serial.print("Acceleration in Y-Axis : ");
  Serial.println(yAccl);
  delay(500);
}

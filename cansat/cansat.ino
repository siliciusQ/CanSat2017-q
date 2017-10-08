#include <qbcan.h>
//#include <Wire.h>
//#include <SPI.h>

BMP180 bmp;
RFM69 radio;

#define NODE_ID     2   // my ID
#define NETWORK_ID  100 // my network
#define GATEWAY_ID  1   // receiver's ID

#define ENCRYPT_KEY "encryptKey"  // must be the same for all nodes


void setup() {
  // debug
  Serial.begin(9600);

  if (bmp.begin())
    Serial.println("BMP180 init succes");
  else
    {Serial.println("BMP180 init fail\n\n"); while(true);}

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Transmitting at 433 Mhz");

}

void loop() {
  double temperature, pressure;
  char radioBuff[50];
  
  bmp.getData(temperature, pressure);
  sprintf(radioBuff, "%d:%d", (int)temperature, (int)pressure);


  Serial.print("Buffer: "); Serial.println(radioBuff);
  Serial.print("Absolute pressure: "); Serial.print(pressure, 2); Serial.println(" mb.");
  Serial.print("Temperature: "); Serial.print(temperature, 2); Serial.println(" deg C.");

  // send data
  radio.send(GATEWAY_ID, radioBuff, 50);
}

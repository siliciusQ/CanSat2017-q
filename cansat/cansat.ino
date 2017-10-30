#include <qbcan.h>
//#include <Wire.h>
//#include <SPI.h>


RFM69 radio;

#define NODE_ID     2   // my ID
#define NETWORK_ID  100 // my network
#define GATEWAY_ID  1   // receiver's ID

#define ENCRYPT_KEY "tiro finale"  // must be the same for all nodes


void setup() {
  // debug
  Serial.begin(9600);

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Transmitting at 433 Mhz");

}

void loop() {
  char radioBuff[50];
  sprintf(radioBuff, "%d", );


  Serial.print("Buffer: "); Serial.println(radioBuff);

  // send data
  radio.send(GATEWAY_ID, radioBuff, 50);
}





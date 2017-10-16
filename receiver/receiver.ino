#include <qbcan.h>

#define NODE_ID 1
#define NETWORK_ID 100
#define ENCRYPT_KEY "tiro finale"

RFM69 radio

void setup() {
  Serial.begin(9600);

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Done initializing...");

}

void loop() {
  

}

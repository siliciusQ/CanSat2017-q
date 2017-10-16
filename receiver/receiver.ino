<<<<<<< HEAD
=======
#include <qbcan.h>

#define NODE_ID 1
#define NETWORK_ID 100
#define ENCRYPT_KEY "tiro finale"

RFM69 radio;

void setup() {
  Serial.begin(9600);

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Done initializing...");

}

void loop() {

  if (radio.receiveDone()) {
    // print additional info
    Serial.println(" < ---  Receive done:  --- >");
    Serial.print("Sender ID:\t"); Serial.print(String(radio.SENDERID)); Serial.print("\n");
    Serial.print("Strength:\t"); Serial.print(String(radio.RSSI)); Serial.print("\n");
    Serial.println();
    //print actual message
    for (byte i=0; i < radio.DATALEN; i++) {
      Serial.print((char)radio.DATA[i]); //print every byte of message
    }
  }

}
>>>>>>> newReceiverDefaultCode

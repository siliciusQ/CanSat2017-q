#include <qbcan.h>


RFM69 radio;

#define NODE_ID     2   // my ID
#define NETWORK_ID  73 // my network
#define GATEWAY_ID  1   // receiver's ID

#define ENCRYPT_KEY "SatForBrainlets"// must be the same for all nodes. 16 bytes (15 char long string)


void setup() {
  // debug
  Serial.begin(9600);
  delay(2000);

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Transmitting at 433 Mhz");

  delay(2000);
}

void loop() {
  static unsigned long message_id = 0;
  byte radioBuff[61] = {0}; //max data length in bytes


  writeToArray(&radioBuff[0], message_id);
  writeToArray(&radioBuff[4], millis());
  sprintf(&radioBuff[8], "hello world!");


  Serial.print("Buffer: ");
  Serial.print( arrayToLong(radioBuff) ); Serial.print(" "); Serial.print( arrayToLong(&radioBuff[4]) ); Serial.print("\n");
  for(byte c=8; c<sizeof(radioBuff); c++){
    Serial.print((char)radioBuff[c]);
  }

  // send data
  radio.send(GATEWAY_ID, radioBuff, 61);
  Serial.println("\n\tSended.");
  message_id += 1;
}

/*
 * message:
 * [id - 4 bytes][time - 4 bytes][some text
 */

void writeToArray(byte * array_, unsigned long val){
  for(byte c=0; c<4; c++){
    array_[c] = lowByte(val);
    val = val >> 8;
  }
}


unsigned long arrayToLong(byte * array_){
  unsigned long answer;
  for (byte a=0; a<4; a++)
    for (byte b=0; b<8; b++)
      bitWrite(answer, (a*8)+b, bitRead(array_[a], b));
  return answer;
}


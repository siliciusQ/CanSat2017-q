#include <qbcan.h>
#include "utility.h"

RFM69 radio;

#define NODE_ID     2   // my ID
#define NETWORK_ID  73 // my network
#define GATEWAY_ID  1   // receiver's ID

#define ENCRYPT_KEY "SatForBrainlets"// must be the same for all nodes. 16 bytes (15 char long string)

#define RADIO_BUFF_SIZE 61

void setup() {
  // debug
  Serial.begin(9600);

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("Transmitting at 433 Mhz");
  
  delay(2000);
}

void loop() {
  static unsigned long message_id = 0;
  char radioBuff[RADIO_BUFF_SIZE] = {0}; //max data length in bytes


  longToArray(&radioBuff[0], message_id);
  longToArray(&radioBuff[4], millis());
  sprintf(&radioBuff[8], " hello world! :DDDDDDD ");


  Serial.print("Buffer: ");
  Serial.print( castArrayTo(unsigned long, &radioBuff[0]) ); Serial.print(" "); Serial.print(castArrayTo(unsigned long, &radioBuff[4])); Serial.print("\n");
  for(byte c=8; c<RADIO_BUFF_SIZE; ++c){
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
 

#include <qbcan.h>

#define NODE_ID 1
#define NETWORK_ID 73
#define ENCRYPT_KEY "SatForBrainlets"


RFM69 radio;

void setup() {
  Serial.begin(9600);
  delay(2000);
  Serial.println("Starting initializing...");

  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  Serial.println("...Done initializing");
  while(!Serial); // wait for serial to initialize
  
  radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
  radio.setHighPower();
  radio.encrypt(ENCRYPT_KEY);
  
  Serial.println("Done initializing...");
  delay(1000);

}


void loop() {
  
  
  if (radio.receiveDone()) {
    // print additional info
    unsigned long messageID = arrayToLong(&radio.DATA[0]);
    unsigned long messageTime = arrayToLong(&radio.DATA[4]);
    
    static unsigned long lastMessageTime = messageTime;
    
    unsigned long messageDifference = messageTime - lastMessageTime;
    lastMessageTime = messageTime;
    
    
    //print actual message
    Serial.print("#["); Serial.print(messageID); Serial.print("][");
    Serial.print(messageDifference); Serial.print("][");
    Serial.print(messageTime); Serial.print("]>>");
    for (byte i=8; i < radio.DATALEN; i++) {
      Serial.print((char)radio.DATA[i]); //print every byte of message
    }
    Serial.print("<<\n");
  }
  //delay(500);

}






unsigned long arrayToLong(byte * array_){
  unsigned long answer;
  for (byte a=0; a<4; a++)
    for (byte b=0; b<8; b++)
      bitWrite(answer, (a*8)+b, bitRead(array_[a], b));
  return answer;
}


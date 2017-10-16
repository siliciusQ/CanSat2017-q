/* 
    qbcan CanSat example.

    This sketch reads temperature and pressure data and sends it to the Ground station
*/

//Include the required libraries
#include <qbcan.h>
#include <Wire.h>
#include <SPI.h>

//Pressure sensor object
BMP180 bmp;


//Radio Parameters
#define NODEID        2    //unique for each node on same network
#define NETWORKID     100  //the same on all nodes that talk to each other
#define GATEWAYID     1    //Receiving node
#define ENCRYPTKEY    "tiro finale" //exactly the same 16 characters/bytes on all nodes!

//Radio object
char payload[50];
RFM69 radio;




void setup()
{
  //Initialize serial connection for debugging
  Serial.begin(9600);
  Serial.println("BOOT");



  // Initialize pressure sensor.
  if (bmp.begin())
    Serial.println("BMP180 init success");
  else
  
  {
    //In case of error let user know of the problem
    Serial.println("BMP180 init fail (disconnected?)\n\n");
    while(1); // Pause forever.
  }

  //Initialize radio
  radio.initialize(FREQUENCY,NODEID,NETWORKID);
  radio.setHighPower(); //To use the high power capabilities of the RFM69HW
  radio.encrypt(ENCRYPTKEY);
  Serial.println("Transmitting at 433 Mhz");

  

}

void loop()
{
  double temperature, pressure;
  // Get a new pressure reading:
  bmp.getData(temperature, pressure);


  //Display data
  Serial.print("Absolute pressure: ");
  Serial.print(pressure,2);
  Serial.println(" mb.");
  Serial.print("Temperature: ");
  Serial.print(temperature,2);
  

  //Send Data
  sprintf(payload,"temperature: %d C, pressure: %d mb.",(int)temperature,(int)pressure);
  Serial.println(payload);
  radio.send(GATEWAYID, payload, 50);
  Serial.println("Send complete");
  
  delay(500);
}

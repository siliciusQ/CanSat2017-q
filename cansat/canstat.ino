#include <qbcan.h>
#include <SD.h>


#define	NODE_ID			2
#define	NETWORKD_ID		73
#define	GATEWAY_ID		1
#define ENCRYPT_KEY		"SatForBrainlets"
#define RADIO_BUFF_SIZE	61

#define CHIP_SELECT		4;

union sULong {
	unsigned long number;
	byte byteArray[sizeof(long)];
};
union buffer {
	byte byte_t[RADIO_BUFF_SIZE];
	char char_t[RADIO_BUFF_SIZE];
};


void arrayCopy(byte *, byte *);


void setup()
{
	Serial.begin(9600);
	
	
	RFM69 radio;
	radio.initialize(FREQUENCY, NODE_ID, NETWORK_ID);
	radio.setHighPower();
	radio.encrypt(ENCRYPT_KEY);
	delay(2000);
	
	SD.begin(CHIP_SELECT);
	File log_file;
	for (char log_name[20], int i=0 ;; ++i) {
		sprintf(log_name, "log_%d.txt", i);
		if (!SD.exist(log_name))
			log_file = SD.open(log_name, FILE_WRITE);
	}
	
	
	union buffer radioBuff = {0};
	union sULong message_count = {0};
	
	while(true)
	{
		union sULong time = {millis()};
		
		
		arrayCopy(message_count.byteArray, radioBuff.byte_t, 4);
		arrayCopy(time.byteArray, &radioBuff.byte_t[3], 4);
		sprintf(&radioBuff.char_t[7], "hello world!");
		
		radio.send(GATEWAY_ID, radioBuff.byte_t, RADIO_BUFF_SIZE);
		log_file.write(radioBuff.byte_t, RADIO_BUFF_SIZE);
		
		++message_count.number;
	}
	
}


void arrayCopy(byte *a1, byte *a2, c)
{
	for (int i=0; i<c; ++i)
		a1[i] = a2[i];
}























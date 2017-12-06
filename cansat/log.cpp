/*
* need <SPI.h>
* need also "utility.h"
*/
#include <SD.h>

const int chipSelect = 4;


int log_init(void)
{
	if (!SD.begin(chipSelect))
		return false;

	char log_name[20]
	for (int i=0 ;; i++) {
		sprintf(log_name, "log_%d.txt", i)
		if (!SD.exist(log_name))
			break
	}

`

}

int log(union Unit *buffer)
{
	;
}
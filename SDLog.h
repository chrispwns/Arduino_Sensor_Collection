#ifndef SDLog_h
#define SDLog_h
#include "SD.h"


class SDLog {
public:
	SDLog(float temperature, float humidity,
	uint8_t day, uint8_t month, uint16_t year,
	uint8_t hour, uint8_t minute, uint8_t second,
	double longitude, double latitude);
	
	void addHeader(File data);
};

#endif

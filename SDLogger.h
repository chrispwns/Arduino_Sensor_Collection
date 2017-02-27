/*
Name:		SDLogger.h
Purpose:	Allows data logging to a file on an inserted SD Card
Created:	2/23/2017
Author:	Christopher Naron
*/
#ifndef SDLogger_h
#define SDLogger_h

class SDLogger {
public:
	SDLogger(float temperature, float humidity, String currentTime, String location);
	void dumpFile();
	void deleteFile();

private:
	void createFile();
	void writeFile(String data);
};
#endif // !SDLogger_h

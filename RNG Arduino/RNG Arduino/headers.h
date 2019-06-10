// headers.h
// Used to prevent inclusion order problems

#ifndef _HEADERS_h
#define _HEADERS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif



//CMD.ino
void splitCMD(String *cmd, int *argc, char ***argv);
void freeCharMat(int *argc, char ***argv);
void commandAnalysis(String *cmd, void(*callback)(String));


//Ethernet.ino
bool initEthernet();
String getEthernetStatus();
String getEthernetIp();
void checkEthernetClient();


//Generate.ino
int getThreshold1();
void setThreshold1(int t);
int getThreshold2();
void setThreshold2(int t);
inline int genValue1();
inline int genValue2();
inline byte genBit();
inline char genBitChar();
inline byte genBit1();
inline byte genBit2();
inline byte genBitVN();
inline char genByteChar();
inline char genByteCharVN();
void adjustThreshold1(long int nb);
void adjustThreshold2(long int nb);


//SD.ino
bool generateSD(long int nb, String filename, bool vn, void(*callback)(String));


//Serial.ino
bool generateSerial(long int nb, bool vn, void(*callback)(String));
void serialSendData(String data);
void serialCommand();



#endif
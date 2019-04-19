/*
 Name:		RNG_Arduino.ino
 Created:	19/04/2019 19:56:56
 Author:	Lucas
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>


int SPI_ADC_PIN = 40;
int SPI_SD_PIN = 4;
int SPI_ETHERNET_PIN = 10;


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(57600, SERIAL_8N1);

	SPI.begin();
	pinMode(SPI_ADC_PIN, OUTPUT);
	digitalWrite(SPI_ADC_PIN, HIGH);
	pinMode(SPI_SD_PIN, OUTPUT);
	digitalWrite(SPI_SD_PIN, HIGH);
	pinMode(SPI_ETHERNET_PIN, OUTPUT);
	digitalWrite(SPI_ETHERNET_PIN, HIGH);
	SPI.setClockDivider(SPI_CLOCK_DIV2);
}

// the loop function runs over and over again until power down or reset
void loop() {
	serialCommand();
}

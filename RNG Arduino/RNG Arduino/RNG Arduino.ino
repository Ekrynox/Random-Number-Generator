/*
 Name:		RNG_Arduino.ino
 Created:	19/04/2019 19:56:56
 Author:	Lucas
*/

#include <SPI.h>
#include <Ethernet.h>
#include <SdFat.h>


#define USE_ADC

#define SPI_SD_PIN 4
#define SPI_ETHERNET_PIN 10
#define SPI_ADC_PIN 40

uint8_t adc_port;
uint8_t adc_bit;
volatile uint8_t *adc_out;

#define CLR_ADC() (*adc_out &= ~adc_bit)
#define SET_ADC() (*adc_out |= adc_bit)


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(57600, SERIAL_8N1);

	SPI.begin();
	pinMode(SPI_SD_PIN, OUTPUT);
	digitalWrite(SPI_SD_PIN, HIGH);
	pinMode(SPI_ETHERNET_PIN, OUTPUT);
	digitalWrite(SPI_ETHERNET_PIN, HIGH);

	
	pinMode(SPI_ADC_PIN, OUTPUT);
	adc_port = digitalPinToPort(SPI_ADC_PIN);
	adc_bit = digitalPinToBitMask(SPI_ADC_PIN);
	adc_out = portOutputRegister(adc_port);
	SET_ADC();
}

// the loop function runs over and over again until power down or reset
void loop() {
	serialCommand();
	/*while (true) {
		Serial.println(genValue());
	}*/
}

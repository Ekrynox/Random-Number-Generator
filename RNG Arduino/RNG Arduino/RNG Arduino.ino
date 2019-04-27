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

#ifdef USE_ADC
	#define SPI_ADC_PIN 40
	uint8_t adc_port;
	uint8_t adc_bit;
	volatile uint8_t *adc_out;

	#define CLR_ADC() (*adc_out &= ~adc_bit)
	#define SET_ADC() (*adc_out |= adc_bit)
#else
	#define INPUT_PIN 22

	uint8_t input_port;
	uint8_t input_bit;
	volatile uint8_t *input_in;

	#define READ_INPUT() (*input_in & input_bit)
#endif


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(57600, SERIAL_8N1);

	SPI.begin();
	pinMode(SPI_SD_PIN, OUTPUT);
	digitalWrite(SPI_SD_PIN, HIGH);
	pinMode(SPI_ETHERNET_PIN, OUTPUT);
	digitalWrite(SPI_ETHERNET_PIN, HIGH);

	#ifdef USE_ADC
		pinMode(SPI_ADC_PIN, OUTPUT);

		adc_port = digitalPinToPort(SPI_ADC_PIN);
		adc_bit = digitalPinToBitMask(SPI_ADC_PIN);
		adc_out = portOutputRegister(adc_port);

		SET_ADC();
	#else
		pinMode(INPUT_PIN, INPUT);
		input_port = digitalPinToPort(INPUT_PIN);
		input_bit = digitalPinToBitMask(INPUT_PIN);
		input_in = portInputRegister(input_port);
	#endif
}

// the loop function runs over and over again until power down or reset
void loop() {
	serialCommand();
}

/*
 Name:		RNG_Arduino.ino
 Created:	19/04/2019 19:56:56
 Author:	Lucas
*/

#include "headers.h"
#include <SPI.h>
#include <Ethernet.h>
#include <SdFat.h>


#define SPI_SD_PIN 30
#define SPI_ETHERNET_PIN 10
#define SPI_ADC_PIN 40
#define SPI_ADC2_PIN 41

#define DEBUG_LED_PIN 13

uint8_t adc_port1;
uint8_t adc_bit1;
volatile uint8_t *adc_out1;
uint8_t adc2_port;
uint8_t adc2_bit;
volatile uint8_t *adc2_out;

#define CLR_ADC1() (*adc_out1 &= ~adc_bit1)
#define SET_ADC1() (*adc_out1 |= adc_bit1)

#define CLR_ADC2() (*adc2_out &= ~adc2_bit)
#define SET_ADC2() (*adc2_out |= adc2_bit)


// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(57600, SERIAL_8N1);

	pinMode(4, OUTPUT);
	digitalWrite(4, HIGH);
	pinMode(31, OUTPUT);
	digitalWrite(31, HIGH);

	SPI.begin();
	pinMode(SPI_SD_PIN, OUTPUT);
	digitalWrite(SPI_SD_PIN, HIGH);
	pinMode(SPI_ETHERNET_PIN, OUTPUT);
	digitalWrite(SPI_ETHERNET_PIN, HIGH);

	pinMode(DEBUG_LED_PIN, OUTPUT);
	digitalWrite(DEBUG_LED_PIN, LOW);

	pinMode(SPI_ADC_PIN, OUTPUT);
	adc_port1 = digitalPinToPort(SPI_ADC_PIN);
	adc_bit1 = digitalPinToBitMask(SPI_ADC_PIN);
	adc_out1 = portOutputRegister(adc_port1);
	SET_ADC1();

	pinMode(SPI_ADC2_PIN, OUTPUT);
	adc2_port = digitalPinToPort(SPI_ADC2_PIN);
	adc2_bit = digitalPinToBitMask(SPI_ADC2_PIN);
	adc2_out = portOutputRegister(adc2_port);
	SET_ADC2();

	loadSave();
}

// the loop function runs over and over again until power down or reset
void loop() {
	serialCommand();
}
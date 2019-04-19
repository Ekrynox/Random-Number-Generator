int value;
char buff;

int threshold = 3800;


int genValue() {
	digitalWrite(SPI_ADC_PIN, LOW);
	value = SPI.transfer16(0x0000);
	digitalWrite(SPI_ADC_PIN, HIGH);
	return value >> 2;
}

int genBit() {
	digitalWrite(SPI_ADC_PIN, LOW);
	value = SPI.transfer16(0x0000);
	digitalWrite(SPI_ADC_PIN, HIGH);

	if ((value >> 2) > threshold) {
		return 1;
	}
	else {
		return 0;
	}
}

char genByte() {
	buff = genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	buff <<= 1;
	buff += genBit();
	return buff;
}

int value;
char buff;

int threshold = 2048 * 4;


int genValue() {
	CLR_ADC();
	value = SPI.transfer16(0x0000);
	SET_ADC();
	return value >> 2;
}

int genBit() {
	CLR_ADC();

	if (SPI.transfer16(0x0000) > threshold) {
		SET_ADC();
		return 1;
	}
	else {
		SET_ADC();
		return 0;
	}
}

char genBitChar() {
	CLR_ADC();

	if (SPI.transfer16(0x0000) > threshold) {
		SET_ADC();
		return '1';
	}
	else {
		SET_ADC();
		return '0';
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

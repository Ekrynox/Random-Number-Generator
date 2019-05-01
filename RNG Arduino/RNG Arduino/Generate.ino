int value;
char buff;

int threshold = 2700 << 2;


inline int genValue() {
	CLR_ADC();
	value = SPI.transfer16(0x0000);
	SET_ADC();
	return value >> 2;
}

inline byte genBit() {
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

inline char genBitChar() {
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

inline byte genBitVN() {
	if (genBit() == 0) {
		if (genBit() == 1) {
			return 0;
		}
		return genBitVN();
	}

	if (genBit() == 0) {
		return 1;
	}
	return genBitVN();
}

inline char genByteChar() {
	char c = 0;
	if (genBit()) {
		c |= 0b10000000;
	}
	if (genBit()) {
		c |= 0b1000000;
	}
	if (genBit()) {
		c |= 0b100000;
	}
	if (genBit()) {
		c |= 0b10000;
	}
	if (genBit()) {
		c |= 0b1000;
	}
	if (genBit()) {
		c |= 0b100;
	}
	if (genBit()) {
		c |= 0b10;
	}
	if (genBit()) {
		c |= 0b1;
	}
	return c;
}
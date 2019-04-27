int value;
char buff;


#ifdef USE_ADC

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

#else

inline byte genBit() {
	if (READ_INPUT()) {
		return 1;
	}
	else {
		return 0;
	}
}

inline char genBitChar() {
	if (READ_INPUT()) {
		return '1';
	}
	else {
		return '0';
	}
}

#endif
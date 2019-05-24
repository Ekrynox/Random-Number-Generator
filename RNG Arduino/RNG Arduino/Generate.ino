int value;

int threshold = 2700 << 2;

int getThreshold() {
	return threshold >> 2;
}

void setThreshold(int t) {
	threshold = t << 2;
}


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


void adjustThreshold(long int nb) {
	long int i, j, k;
	int n = 4;
	int oldt;
	int t = 4096 / 2;
	setThreshold(t);

	k = 0;
	for (i = 0; i < nb; i++) {
		k += genBit();
	}

	while (4096 / n > 0) {
		oldt = t;
		if (nb - k < k) {
			t += 4096 / n;
		}
		else {
			t -= 4096 / n;
		}
		setThreshold(t);

		j = 0;
		for (i = 0; i < nb; i++) {
			j += genBit();
		}

		if (abs(nb - 2 * j) > abs(nb - 2 * k)) {
			t = oldt;
			setThreshold(t);
		}
		else {
			k = j;
		}

		n *= 2;
	}
}
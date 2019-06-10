int value;

int threshold1 = 1080 << 2;
int threshold2 = 1080 << 2;


int getThreshold1() {
	return threshold1 >> 2;
}

void setThreshold1(int t) {
	threshold1 = t << 2;
}

int getThreshold2() {
	return threshold2 >> 2;
}

void setThreshold2(int t) {
	threshold2 = t << 2;
}


inline int genValue1() {
	CLR_ADC1();
	value = SPI.transfer16(0x0000);
	SET_ADC1();
	return value >> 2;
}

inline int genValue2() {
	CLR_ADC2();
	value = SPI.transfer16(0x0000);
	SET_ADC2();
	return value >> 2;
}


inline byte genBit() {
	CLR_ADC1();

	if (SPI.transfer16(0x0000) > threshold1) {
		SET_ADC1();

		CLR_ADC2();

		if (SPI.transfer16(0x0000) > threshold2) {
			SET_ADC2();
			return 0;
		}
		SET_ADC2();

		return 1;
	}

	SET_ADC1();

	CLR_ADC2();

	if (SPI.transfer16(0x0000) > threshold2) {
		SET_ADC2();
		return 1;
	}
	SET_ADC2();

	return 0;
}

inline char genBitChar() {
	CLR_ADC1();

	if (SPI.transfer16(0x0000) > threshold1) {
		SET_ADC1();

		CLR_ADC2();

		if (SPI.transfer16(0x0000) > threshold2) {
			SET_ADC2();
			return '0';
		}
		SET_ADC2();

		return '1';
	}
	
	SET_ADC1();

	CLR_ADC2();

	if (SPI.transfer16(0x0000) > threshold2) {
		SET_ADC2();
		return '1';
	}
	SET_ADC2();

	return '0';
}


inline byte genBit1() {
	CLR_ADC1();

	if (SPI.transfer16(0x0000) > threshold1) {
		SET_ADC1();

		return 1;
	}

	SET_ADC1();

	return 0;
}

inline byte genBit2() {
	CLR_ADC2();

	if (SPI.transfer16(0x0000) > threshold2) {
		SET_ADC2();

		return 1;
	}

	SET_ADC2();

	return 0;
}


inline byte genBitVN() {
	while (1) {
		if (genBit() == 0) {
			if (genBit() == 1) {
				return 0;
			}
		} else {
			if (genBit() == 0) {
				return 1;
			}
		}
	}
}

inline char genBitCharVN() {
	while (1) {
		if (genBit() == 0) {
			if (genBit() == 1) {
				return '0';
			}
		}
		else {
			if (genBit() == 0) {
				return '1';
			}
		}
	}
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

inline char genByteCharVN() {
	char c = 0;
	if (genBitVN()) {
		c |= 0b10000000;
	}
	if (genBitVN()) {
		c |= 0b1000000;
	}
	if (genBitVN()) {
		c |= 0b100000;
	}
	if (genBitVN()) {
		c |= 0b10000;
	}
	if (genBitVN()) {
		c |= 0b1000;
	}
	if (genBitVN()) {
		c |= 0b100;
	}
	if (genBitVN()) {
		c |= 0b10;
	}
	if (genBitVN()) {
		c |= 0b1;
	}
	return c;
}


void adjustThreshold1(long int nb) {
	long int i, j, k;
	int n = 4;
	int oldt;
	int t = 4096 / 2;
	setThreshold1(t);

	k = 0;
	for (i = 0; i < nb; i++) {
		k += genBit1();
	}

	while (4096 / n > 0) {
		oldt = t;
		if (nb - k < k) {
			t += 4096 / n;
		}
		else {
			t -= 4096 / n;
		}
		setThreshold1(t);

		j = 0;
		for (i = 0; i < nb; i++) {
			j += genBit1();
		}

		if (abs(nb - 2 * j) > abs(nb - 2 * k)) {
			t = oldt;
			setThreshold1(t);
		}
		else {
			k = j;
		}

		n *= 2;
	}
}

void adjustThreshold2(long int nb) {
	long int i, j, k;
	int n = 4;
	int oldt;
	int t = 4096 / 2;
	setThreshold2(t);

	k = 0;
	for (i = 0; i < nb; i++) {
		k += genBit2();
	}

	while (4096 / n > 0) {
		oldt = t;
		if (nb - k < k) {
			t += 4096 / n;
		}
		else {
			t -= 4096 / n;
		}
		setThreshold2(t);

		j = 0;
		for (i = 0; i < nb; i++) {
			j += genBit2();
		}

		if (abs(nb - 2 * j) > abs(nb - 2 * k)) {
			t = oldt;
			setThreshold2(t);
		}
		else {
			k = j;
		}

		n *= 2;
	}
}
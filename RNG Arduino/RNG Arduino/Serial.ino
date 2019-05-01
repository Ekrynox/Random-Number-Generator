bool generateSerial(long int nb) {
	int i;
	nb = ceil(nb / 8.0);

	for (i = 0; i < nb; i++) {
		Serial.write(genByteChar());
	}

	return true;
}


bool generateSerialVN(long int nb) {
	int i, j;
	nb = ceil(nb / 8.0);
	char c;

	for (i = 0; i < nb; i++) {
		c = 0;
		j = 7;
		while (j >= 0) {
			if (!genBit()) {
				if (genBit()) {
					c += 1 << j--;
				}
			}
			else {
				if (!genBit()) {
					j--;
				}
			}
		}
		Serial.write(c);
	}

	return true;
}
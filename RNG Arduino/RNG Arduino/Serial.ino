bool generateSerial(long int nb) {
	int i;

	for (i = 0; i < nb; i++) {
		Serial.write(genBitChar());
	}

	return true;
}


bool generateSerialVN(long int nb) {
	int i;

	for (i = 0; i < nb;) {
		if (genBit()) {
			if (!genBit()) {
				Serial.write('1');
				i++;
			}
		}
		if (!genBit()) {
			if (genBit()) {
				Serial.write('0');
				i++;
			}
		}
	}

	return true;
}


void serialCommand() {
	if (Serial.available() > 0) {
		String cmd = Serial.readStringUntil('\n');
		digitalWrite(DEBUG_LED_PIN, HIGH);
		Serial.println(commandAnalysis(&cmd));
		digitalWrite(DEBUG_LED_PIN, LOW);
	}
}
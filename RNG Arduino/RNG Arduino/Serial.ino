bool generateSerial(long int nb, bool vn, void(*callback)(String)) {
	int i;
	nb = ceil(nb / 8.0);

	(*callback)("OK");

	unsigned long start = millis();

	if (vn) {
		for (i = 0; i < nb; i++) {
			Serial.write(genByteCharVN());
		}
	}
	else {
		for (i = 0; i < nb; i++) {
			Serial.write(genByteChar());
		}
	}

	unsigned long end = millis();
	delay(2000);
	(*callback)(String(end - start) + "ms");

	return true;
}


void serialSendData(String data) {
	Serial.println(data);
	Serial.flush();
}


void serialCommand() {
	if (Serial.available() > 0) {
		String cmd = Serial.readStringUntil('\n');
		digitalWrite(DEBUG_LED_PIN, HIGH);
		commandAnalysis(&cmd, &serialSendData);
		digitalWrite(DEBUG_LED_PIN, LOW);
	}
}